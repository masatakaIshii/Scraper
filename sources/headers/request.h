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
#include "urlHelper.h"


/**
 * Initialise Request structure
 * @param url : url to get
 * @return *Request
 */
Request *initRequest(const char *url);

/**
 * Get the file extension depends to mime type
 * @param pRequest
 * @return
 * 1 : Success to set extention file in structure UrlHelper
 * 0 : not set because of not found extention file depend to mime type
 */
int getFileExtByMimeType(Request *pRequest);

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
