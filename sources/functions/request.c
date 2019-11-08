/*
 *  Filename    : request.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : request structure and functions
 */

#include "../headers/request.h"

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
    pRequest->isUrlHelper = 0;

    pRequest->pUrlHelper = initUrlHelper(url);
    verifyPointer(pRequest->pUrlHelper->url, "problem pRequest\n");
    pRequest->isUrlHelper = 1;

    pRequest->contentType = NULL;
    pRequest->isContentType = 0;

    return pRequest;
}

static int writeDataInNothing(void *ptr, int size, int numberElements, char *str) {

    return size * numberElements;
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
    int written = (int) fwrite(ptr, size, numberElements, (FILE *) stream);

    return written;
}

static void setOptionsCurlGetMimeType(Request *pRequest) {
    char *str = NULL;
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->pUrlHelper->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ERRORBUFFER, pRequest->errBuf);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInNothing);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, str);
}

/**
 * Function to set all options before perform curl request
 * @param pRequest : pointer of structure Request
 */
static void setOptionsCurlSaveFile(Request *pRequest) {
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
    char *strInSemiColon = NULL;
    int length = 0;

    result = curl_easy_getinfo(pRequest->pHandle, CURLINFO_CONTENT_TYPE, &contentType);

    if (result == CURLE_OK && pRequest->isContentType == 0) {
        strInSemiColon = strchr(contentType, ';');
        length = (strInSemiColon == NULL) ? strlen(contentType) : (int)(strInSemiColon - contentType);
        pRequest->contentType = strMallocCpy(contentType, length);
        if (pRequest->contentType == NULL) {
            destroyRequest(pRequest);
            exit(1);
        }
        pRequest->isContentType = 1;
    }

    return result;
}

/**
 * Function to check if response code is 200
 * @param pRequest : pointer of structure response
 * @param result : result of curl perform
 * @return
 * 0 : response code is 200
 * -1 : response code is not 200 so not OK
 */
static int checkIfResponseCodeIsOk(Request *pRequest, CURLcode result) {
    long responseCode = 0;
    curl_easy_getinfo(pRequest->pHandle, CURLINFO_RESPONSE_CODE, &responseCode);
    if (responseCode == 200 && result != CURLE_ABORTED_BY_CALLBACK) {
        return 0;
    }

    return -1;
}

/**
 * fetch few response informations
 * @param pRequest
 * @param result
 * @return
 * -1 : the response code is not 200
 * CURLcode number : depend to the result of curl_easy_getinfo function;
 */
static int fetchResponseInfo(Request *pRequest, CURLcode result) {
    if (checkIfResponseCodeIsOk(pRequest, result) == -1) {
        return -1;
    }

    return saveContentType(pRequest);
}

static void setHandle(Request *pRequest) {
    pRequest->pHandle = curl_easy_init();
    verifyPointer(pRequest->pHandle, "Problem curl easy init\n");

    pRequest->isHandleInit = 1;
}

/**
 * Function to get ext file by mime type
 * @param pRequest
 * @return
 */
int getExtFileByMimeType(Request *pRequest) {
    // TODO : get the ext file by mime type when the file extension is not in url
    //fprintf(stderr, "The function to get file extention by mime type is not implemented, maybe soon\n");
    int result;
    setHandle(pRequest);

    setOptionsCurlGetMimeType(pRequest);
    result = curl_easy_perform(pRequest->pHandle);
    if (result == CURLE_OK) {
        result = saveContentType(pRequest);
        result = (result == CURLE_OK) ? setExtFileInFileName(pRequest->pUrlHelper, pRequest->contentType) : result;
    } else {
        clearPHandle(pRequest->pHandle);
        return (int) result;
    }

    return result;
}

/**
 * function to set stream file and handle to save request in file
 */
static void setStreamAndHandle(Request *pRequest, char *fileName) {

    setHandle(pRequest);

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
    setOptionsCurlSaveFile(pRequest);

    result = curl_easy_perform(pRequest->pHandle);
    if (result == CURLE_OK) {
        result = fetchResponseInfo(pRequest, result);
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