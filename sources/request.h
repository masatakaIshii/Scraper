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
    char *contentType;
    char errBuf[CURL_ERROR_SIZE];
} Request;

Request *initRequest(char *url);

static int writeDataInFile(void *ptr, int size, int numberElements, void *stream);

static void setOptionsCurl(Request *pRequest);

static int saveContentType(Request *pRequest);

int saveRequestInFile(Request *pRequest, char *savePath);

int initPFile(char *outputPath, char *mode);

void clearPHandle(Request *pRequest) ;

void clearPFile(Request *pRequest);

void destroyRequest(Request *pRequest);

#endif //SCRAPER_REQUEST_H
