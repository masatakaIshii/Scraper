/*
 *  Filename    : urlHelper.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to decompose and manage parts of URL
 */
#ifndef SCRAPER_URLHELPER_H
#define SCRAPER_URLHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "common.h"
#include "app.h"
#include "../headers/fileExtTypeMime.h"

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return OK pUrlHerper : pointer of structure UrlHelper,<br>
 * ERROR NULL
 */
UrlHelper *initUrlHelper(const char *url);

/**
 * Function to set file name when there are not indicated in URL
 * @param pUrlHelper
 * @param fileNameNoExt
 * @param mimeType
 * @return OK 1, ERROR 0, WARNING 2
 */
int setFileNameWhenNoOneInUrl(UrlHelper *pUrlHelper, const char *fileNameNoExt, char *mimeType);

/**
 * Function to set file extension in file name
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param mimeType : the mime type to get file extension
 * @return OK 1, ERROR 0, WARNING 2
 */
int setFileExtInFileName(UrlHelper *pUrlHelper, char *mimeType);

/**
 * Destroy the pointer of structure UrlHelper
 * @param pUrlHelper
 */
void destroyUrlHelper(UrlHelper *pUrlHelper);

#endif //SCRAPER_URLHELPER_H
