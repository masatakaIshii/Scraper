/*
 *  Filename    : request.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : request structure and functions
 */
#ifndef SCRAPER_REQUEST_H
#define SCRAPER_REQUEST_H

#include <stdio.h>
#include <curl/curl.h>
#include "common.h"

typedef struct Request {
    CURL *pHandle;
    int isHandleInit;
    FILE *pFile;
    int isFileOpen;
    char *url;
    char errBuf[CURL_ERROR_SIZE];
} Request;

Request *initRequest(char *url);

int saveRequestInFile(Request *pRequest, char *savePath);

int initPFile(char *outputPath, char *mode);

void clearPHandle(Request *pRequest) ;

int clearPFile(Request *request);

int destroyRequest(Request *request);

#endif //SCRAPER_REQUEST_H
