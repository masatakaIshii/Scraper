//
// Created by masat on 27/10/2019.
//

#ifndef SCRAPER_URLHELPER_H
#define SCRAPER_URLHELPER_H

#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
#include "common.h"

typedef enum UrlHelperResponse {
    UH_OK,
    UH_NAME_PB,
    UH_MEM_URL_PB,
    UH_EXT_FILE_NOT_FOUND
} UHRes;

typedef struct UrlHelper {
    char *url;
    char *domainName;
    char *fileName;
    char *extFile;
    int isDomainName;
    int isFileName;
    int isExtFile;
    UHRes result;
} UrlHelper;

UrlHelper *initUrlHelper(const char *url);

static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url);

void urlHelperSetDomainName(UrlHelper *pUrlHelper);

void urlHelperSetFileName(UrlHelper *pUrlHelper);

void destroyUrlHelper(UrlHelper *pUrlHelper);
/*
UHRes searchAfterComProtocol(char *url, char **fileName);

UHRes haveFileExt(char *url, char **fileName);

void checkUrl(UrlHelper *pUrlHelper, const char *url);
*/
#endif //SCRAPER_URLHELPER_H
