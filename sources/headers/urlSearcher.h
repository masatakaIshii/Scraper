//
// Created by masat on 12/11/2019.
//

#ifndef SCRAPER_URLSEARCHER_H
#define SCRAPER_URLSEARCHER_H

#include <stdio.h>

char **getAllUrlsInPage(const char *UrlNoRes, const char *contentType, const char *page, int *count);

#endif //SCRAPER_URLSEARCHER_H
