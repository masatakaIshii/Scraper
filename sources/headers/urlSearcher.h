//
// Created by masat on 12/11/2019.
//

#ifndef SCRAPER_URLSEARCHER_H
#define SCRAPER_URLSEARCHER_H

#include <stdio.h>
#
#include "struct.h"
#include "urlHelper.h"
#include "lists/listChar.h"

char **getAllUrlsInPage(const char *urlNoRes, const char *contentType, const char *page, int *count);

#endif //SCRAPER_URLSEARCHER_H
