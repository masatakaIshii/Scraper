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

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return : pointer of structure UrlHelper
 */
UrlHelper *initUrlHelper(const char *url);

/**
 * Destroy the pointer of structure UrlHelper
 * @param pUrlHelper
 */
void destroyUrlHelper(UrlHelper *pUrlHelper);

/**
 * Get the file extension depends to mime type
 * @param pUrlHelper
 * @return
 * 1 : Success to set extention file in structure UrlHelper
 * 0 : not set because of not found extention file depend to mime type
 */
int getExtFileByMimeType(UrlHelper *pUrlHelper);

#endif //SCRAPER_URLHELPER_H
