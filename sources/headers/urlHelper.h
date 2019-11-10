//
// Created by masat on 27/10/2019.
//

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
 * @return : pointer of structure UrlHelper
 */
UrlHelper *initUrlHelper(const char *url);

int setFileNameWhenNoOneInUrl(UrlHelper *pUrlHelper, const char *fileNameNoExt, char *mimeType);

int setFileExtInFileName(UrlHelper *pUrlHelper, char *mimeType);

/**
 * Destroy the pointer of structure UrlHelper
 * @param pUrlHelper
 */
void destroyUrlHelper(UrlHelper *pUrlHelper);

#endif //SCRAPER_URLHELPER_H
