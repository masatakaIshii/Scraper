/*
 *  Filename    : request.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : request structure and functions
 */

#include "request.h"

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

    pRequest->mimeType = NULL;

    return pRequest;
}

static int writeDataInFile(void *ptr, int size, int numberElements, void *stream) {
    int written = fwrite(ptr, size, numberElements, (FILE *)stream);

    return written;
}

void setOptionsCurl(Request *pRequest) {
    curl_easy_setopt(pRequest->pHandle, CURLOPT_URL, pRequest->url);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEFUNCTION, writeDataInFile);
    curl_easy_setopt(pRequest->pHandle, CURLOPT_WRITEDATA, pRequest->pFile); // finish save file by request
}

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

    return (int)result;
}

void clearPHandle(Request *pRequest) {
    if (pRequest->isHandleInit != 0) {
        curl_easy_cleanup(pRequest->pHandle);
        pRequest->pHandle = NULL;
        pRequest->isHandleInit = 0;
    }
}

int clearPFile(Request *pRequest) {
    if (pRequest->isFileOpen != 0) {
        fclose(pRequest->pFile);
        pRequest->pFile = NULL;
        pRequest->isFileOpen = 0;
    }
}

int destroyRequest(Request *pRequest) {
    clearPHandle(pRequest);
    clearPFile(pRequest);
    if (pRequest->url != NULL) {
        free(pRequest->url);
        pRequest->url = NULL;
    }
    pRequest->mimeType = NULL;
}