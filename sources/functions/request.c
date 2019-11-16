/*
 *  Filename    : request.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : request structure and functions
 */

#include "../headers/request.h"

static void setStreamAndHandle(Request *pRequest, char *fileName);
static void setHandle(Request *pRequest);
static void setOptionsCurlSaveFile(Request *pRequest);
static int writeDataInNothing(void *ptr, int size, int numberElements, char *str);
static int fetchResponseInfo(Request *pRequest, CURLcode result);
static int setContentType(Request *pRequest, const char *dirPath);

static void setOptionsCurlGetMimeType(Request *pRequest);

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
    if (pRequest->pUrlHelper == NULL) {
        fprintf(stderr, "Problem in url : %s\n", url);
        free(pRequest);
        return NULL;
    }
    pRequest->isUrlHelper = 1;

    pRequest->contentType = NULL;
    pRequest->isContentType = 0;

    return pRequest;
}

/**
 * Function to save request GET content in file
 * @param pRequest : pointer of structure Request
 * @param fileName : name file
 * @return OK result == 0 : result of curl request, ERROR result != 0
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
 * Function to set stream file and handle to save request in file
 * @param pRequest : pointer of structure Request
 * @param fileName : the name of file to create
 */
static void setStreamAndHandle(Request *pRequest, char *fileName) {

    setHandle(pRequest);

    pRequest->pFile = fopen(fileName, "wb");
    verifyPointer(pRequest->pFile, "Problem with open file\n");

    pRequest->isFileOpen = 1;
}

/**
 * Init the handle correspond to the pointer  structure CURL to send the request
 * @param pRequest : pointer of structure Request
 */
static void setHandle(Request *pRequest) {
    pRequest->pHandle = curl_easy_init();
    verifyPointer(pRequest->pHandle, "Problem curl easy init\n");

    pRequest->isHandleInit = 1;
}

/**
 * write data in void
 * @param ptr
 * @param size
 * @param numberElements
 * @param str
 * @return size multiply to numberElements
 */
static int writeDataInNothing(void *ptr, int size, int numberElements, char *str) {

    return size * numberElements;
}

/**
 * Callback function to write get data in file during response of curl
 * @param ptr : pointer of data to write in file
 * @param size : size of the data
 * @param numberElements : number of one data's elements
 * @param stream : file's stream
 * @return
 * OK : writtin != number character of file,<br>
 * ERROR : written != number character of file
 */
static int writeDataInFile(void *ptr, int size, int numberElements, void *stream) {
    int written = (int) fwrite(ptr, size, numberElements, (FILE *) stream);

    return written;
}

/**
 * Function to set all options before perform curl request
 * @param pRequest : pointer of structure Request
 */
static void setOptionsCurlSaveFile(Request *pRequest) {
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->pUrlHelper->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ERRORBUFFER, pRequest->errBuf);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInFile);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, pRequest->pFile); // finish save file by request
}

/**
 * Function to save content type name of request GET
 * @param pRequest : structure of request
 * @return OK : result == 0, ERROR : result != 0
 */
static int saveContentType(Request *pRequest) {
    CURLcode result;
    char *contentType;
    char *strInSemiColon = NULL;
    int length = 0;

    result = curl_easy_getinfo(pRequest->pHandle, CURLINFO_CONTENT_TYPE, &contentType);

    if (result == CURLE_OK && pRequest->isContentType == 0) {
        strInSemiColon = strchr(contentType, ';');
        length = (strInSemiColon == NULL) ? (int)strlen(contentType) : (int)(strInSemiColon - contentType);
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
 * OK : 0 => response code is 200,<br>
 * ERROR : -1 => response code is not 200 so not OK
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
 * Fetch few response informations
 * @param pRequest
 * @param result
 * @return
 * OK : 0 => the result of curl_easy_getinfo function return CURLE_OK,<br>
 * ERROR : -1 => the response code is not 200
 */
static int fetchResponseInfo(Request *pRequest, CURLcode result) {
    if (checkIfResponseCodeIsOk(pRequest, result) == -1) {
        return -1;
    }

    return saveContentType(pRequest);
}

/**
 * Function to get mime type by request and set concerned file extension in file name
 * @param pRequest : pointer of structure Request
 * @param dirResourcePath : directory path of Session
 * @return OK : result == 1, ERROR : result == 0
 */
int getFileExtByMimeType(Request *pRequest, const char *dirResourcePath) {
    int result;
    setHandle(pRequest);

    setOptionsCurlGetMimeType(pRequest);
    result = curl_easy_perform(pRequest->pHandle);
    if (result == CURLE_OK) {
        result = setContentType(pRequest, dirResourcePath);
    } else {
        clearPHandle(pRequest->pHandle);
        return (int) result;
    }

    return result == 0;
}

/**
 * Function to set the content type
 * @param pRequest : pointer of structure Request
 * @param dirResourcePath : normally the directory path of session, not of resource
 * @return OK : result == 0, ERROR : result != 0
 */
static int setContentType(Request *pRequest, const char *dirResourcePath) {
    int result = 0;
    UrlHelper *pUrlHelper = pRequest->pUrlHelper;

    result = saveContentType(pRequest);
    if (result == CURLE_OK) {
        if (pRequest->isContentType == 1) {
            if (pUrlHelper->isFileName == 0) {
                pUrlHelper->fileName = getAvailableFileName(dirResourcePath, "index", "all_files_names.txt", "_scrap_");
                if (pUrlHelper->fileName == NULL) {
                    return 0;
                }
                pUrlHelper->isFileName = 1;
            }
            result = (setFileExtInFileName(pUrlHelper, pRequest->contentType) == 1) ? 0 : -1;
        }
    }

    return result;
}

/**
 * Function to set option in handle of pRequest
 * @param pRequest
 */
static void setOptionsCurlGetMimeType(Request *pRequest) {
    char *str = NULL;
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->pUrlHelper->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ERRORBUFFER, pRequest->errBuf);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInNothing);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, str);
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