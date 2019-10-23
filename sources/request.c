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
Request *initRequest(char *url) {
    Request *pRequest = malloc(sizeof(Request));
    if (pRequest == NULL) {
        errorQuit("Problem malloc pRequest\n");
    }
    pRequest->isFileOpen = 0;
    pRequest->isHandleInit = 0;
    pRequest->url = calloc(strlen(url) + 1, sizeof(char));
    if (pRequest->url == NULL) {
        destroyRequest(pRequest);
        errorQuit("problem pRequest\n");
    }

    strncpy(pRequest->url, url, strlen(url));

    pRequest->contentType = NULL;

    return pRequest;
}

/**
 * Callback function to write get data in file
 * @param ptr : pointer of data to write in file
 * @param size : size of the data
 * @param numberElements : number of one data's elements
 * @param stream : file's stream
 * @return : writtin : number character of file
 */
static int writeDataInFile(void *ptr, int size, int numberElements, void *stream) {
    int written = fwrite(ptr, size, numberElements, (FILE *)stream);

    return written;
}

/**
 * Function to set all options before perform curl request
 * @param pRequest : pointer of structure Request
 */
static void setOptionsCurl(Request *pRequest) {
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInFile);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, pRequest->pFile); // finish save file by request
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ERRORBUFFER, pRequest->errBuf);
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
    } else {
        printf("ERROR curl_easy_getinfo: %s", pRequest->errBuf);
    }

    return result;
}

/**
 * Function to save request GET content in file
 * @param pRequest : pointer of structure Request
 * @param fileName : name file
 * @return result : result of curl request
 */
int saveRequestInFile(Request *pRequest, char *fileName) {
    CURLcode result;
    pRequest->pHandle = curl_easy_init();
    if (pRequest->pHandle == NULL) {
        destroyRequest(pRequest);
        errorQuit("Problem curl easy init\n");
    }
    pRequest->isHandleInit = 1;

    pRequest->pFile = fopen(fileName, "wb");
    if (pRequest->pFile == NULL) {
        destroyRequest(pRequest);
        errorQuit("Problem with open file\n");
    }
    pRequest->isFileOpen = 1;

    setOptionsCurl(pRequest);

    result = curl_easy_perform(pRequest->pHandle);
    if (result == CURLE_OK) {
        result = saveContentType(pRequest);
    } else {
        printf("ERROR curl_easy_perform: %s", pRequest->errBuf);
    }

    return (int)result;
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
 */
void clearPFile(Request *pRequest) {
    if (pRequest->isFileOpen != 0 && pRequest->pFile != NULL) {
        fclose(pRequest->pFile);
        pRequest->pFile = NULL;
        pRequest->isFileOpen = 0;
    }
}

void destroyRequest(Request *pRequest) {
    clearPHandle(pRequest);
    clearPFile(pRequest);

    if (pRequest->url != NULL) {
        free(pRequest->url);
        pRequest->url = NULL;
    }
    if (pRequest->contentType != NULL) {
        free(pRequest->contentType);
        pRequest->contentType = NULL;
    }

    free(pRequest);
}