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

typedef struct Request {
    CURL *pHandle;
    FILE *pFile;
    char *url;
    char errBuf[CURL_ERROR_SIZE];
} Request;

Request *initRequest();

void setOptionCurl(Request *request, CURLoption *options, int nbrOptions);

int saveFile(Request *request, char *savePath);

int clearPHandle(Request *request);

int clearPFile(Request *request);

int destroyRequest(Request *request);

#endif //SCRAPER_REQUEST_H
