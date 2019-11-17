//
// Created by masat on 12/11/2019.
//

#ifndef SCRAPER_URLSEARCHER_H
#define SCRAPER_URLSEARCHER_H

#include <stdio.h>

#include "struct.h"
#include "urlHelper.h"
#include "lists/listChar.h"

UrlSearcher *initUrlSearcher(const char *url, const char *filePath);

char **getAllUrlsInPage(const char *url, const char *contentType, const char *filePath, int *count);



void destroyUrlSearcher(UrlSearcher *pUrlSearcher);

#endif //SCRAPER_URLSEARCHER_H
