/*
 *  Filename    : urlSearcher.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Get the HTTP and HTTPS urls in one page html
 */

#ifndef SCRAPER_URLSEARCHER_H
#define SCRAPER_URLSEARCHER_H

#include <stdio.h>

#include "struct.h"
#include "urlHelper.h"
#include "lists/listChar.h"

UrlSearcher *initUrlSearcher(const char *url, const char *filePath);

char **getAllUrlsInPage(const char *url, const char *contentType, const char *filePath, int *count, const char *dirPath);

void destroyUrlSearcher(UrlSearcher *pUrlSearcher);

#endif //SCRAPER_URLSEARCHER_H
