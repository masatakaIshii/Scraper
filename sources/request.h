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

/**
 * Initialise Request structure
 * @param url : url to get
 * @return *Request
 */
Request *initRequest(char *url);

/**
 * Callback function to write get data in file during response of curl
 * @param ptr : pointer of data to write in file
 * @param size : size of the data
 * @param numberElements : number of one data's elements
 * @param stream : file's stream
 * @return : writtin : number character of file
 */
static int writeDataInFile(void *ptr, int size, int numberElements, void *stream);

/**
 * Function to set all options before perform curl request
 * @param pRequest : pointer of structure Request
 */
static void setOptionsCurl(Request *pRequest);

/**
 * Function to save content type name of request GET
 * @param pRequest : structure of request
 * @return : result : result of request curl
 */
static int saveContentType(Request *pRequest);

/**
 * Function to save request GET content in file
 * @param pRequest : pointer of structure Request
 * @param fileName : name file
 * @return result : result of curl request
 */
int saveRequestInFile(Request *pRequest, char *savePath);

/**
 * Function to clean pointer of type curl in Request structure
 * @param pRequest : structure of Request
 */
void clearPHandle(Request *pRequest);

/**
 * Function to close stream of file in Request structure
 * @param pRequest : structure of Request
 */
void clearPFile(Request *pRequest);

/**
 * Function to free all memory allocation in Request structure
 * @param pRequest : structure of Request
 */
void destroyRequest(Request *pRequest);

#endif //SCRAPER_REQUEST_H
