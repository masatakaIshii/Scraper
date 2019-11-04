/*
 *  Filename    : request.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : request structure and functions
 */

#include "request.h"

/**
 * Initialise Request structure
 * @param url : url to get
 * @return *Request
 */
Request *initRequest(const char *url) {
    Request *pRequest = malloc(sizeof(Request));
    verifyPointer(pRequest, "Problem malloc pRequest\n");
    pRequest->isFileOpen = 0;
    pRequest->isHandleInit = 0;
    pRequest->pUrlHelper = initUrlHelper(url);
    verifyPointer(pRequest->pUrlHelper->url, "problem pRequest\n");

    strcpy(pRequest->pUrlHelper->url, url);

    pRequest->contentType = NULL;

    return pRequest;
}

/**
 * Callback function to write get data in file during response of curl
 * @param ptr : pointer of data to write in file
 * @param size : size of the data
 * @param numberElements : number of one data's elements
 * @param stream : file's stream
 * @return : writtin : number character of file
 */
static int writeDataInFile(void *ptr, int size, int numberElements, void *stream) {
    int written = fwrite(ptr, size, numberElements, (FILE *) stream);

    return written;
}

/**
 * Function to set all options before perform curl request
 * @param pRequest : pointer of structure Request
 */
static void setOptionsCurl(Request *pRequest) {
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->pUrlHelper->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ERRORBUFFER, pRequest->errBuf);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInFile);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, pRequest->pFile); // finish save file by request
}

/**
 * Function to save content type name of request GET
 * @param pRequest : structure of request
 * @return : result : result of request curl
 */
static int saveContentType(Request *pRequest) {
    CURLcode result;
    char *contentType;

    result = curl_easy_getinfo(pRequest->pHandle, CURLINFO_CONTENT_TYPE, &contentType);

    if (result == CURLE_OK) {
        pRequest->contentType = calloc(strlen(contentType) + 1, sizeof(char));
        if (pRequest->contentType == NULL) {
            destroyRequest(pRequest);
            exit(1);
        }
        strcpy(pRequest->contentType, contentType);
    }

    return result;
}

/**
 * function to set stream file and handle to save request in file
 */
static void setStreamAndHandle(Request *pRequest, char *fileName) {

    pRequest->pHandle = curl_easy_init();
    verifyPointer(pRequest->pHandle, "Problem curl easy init\n");

    pRequest->isHandleInit = 1;

    pRequest->pFile = fopen(fileName, "wb");
    verifyPointer(pRequest->pFile, "Problem with open file\n");

    pRequest->isFileOpen = 1;
}

/**
 * Function to save request GET content in file
 * @param pRequest : pointer of structure Request
 * @param fileName : name file
 * @return result : result of curl request
 */
int saveRequestInFile(Request *pRequest, char *fileName) {
    CURLcode result;

    if (pRequest->pUrlHelper->isDomainName != 1) {
        strcpy(pRequest->errBuf, "ERROR Domain name is not correct");
        return CURLE_URL_MALFORMAT;
    }
    setStreamAndHandle(pRequest, fileName);
    setOptionsCurl(pRequest);

    result = curl_easy_perform(pRequest->pHandle);
    if (result == CURLE_OK) {
        result = saveContentType(pRequest);
    } else {
        clearPHandle(pRequest->pHandle);
        clearPFile(pRequest);
        remove(fileName);
    }

    return (int) result;
}

/**
 * Function to clean pointer of type curl in Request structure
 * @param pRequest : structure of Request
 */
void clearPHandle(Request *pRequest) {
    if (pRequest->isHandleInit != 0 && pRequest->pHandle != NULL) {
        curl_easy_cleanup(pRequest->pHandle);
        pRequest->pHandle = NULL;
        pRequest->isHandleInit = 0;
    }
}

/**
 * Function to close stream of file in Request structure
 * @param pRequest : structure of Request
 */
void clearPFile(Request *pRequest) {
    if (pRequest->isFileOpen != 0 && pRequest->pFile != NULL) {
        fclose(pRequest->pFile);
        pRequest->pFile = NULL;
        pRequest->isFileOpen = 0;
    }
}

/**
 * Function to free all memory allocation in Request structure
 * @param pRequest : structure of Request
 */
void destroyRequest(Request *pRequest) {
    clearPHandle(pRequest);
    clearPFile(pRequest);

    if (pRequest->pUrlHelper != NULL) {
        destroyUrlHelper(pRequest->pUrlHelper);
        pRequest->pUrlHelper = NULL;
    }
    if (pRequest->contentType != NULL) {
        free(pRequest->contentType);
        pRequest->contentType = NULL;
    }

    free(pRequest);
}