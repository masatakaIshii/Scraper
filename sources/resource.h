//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RESOURCE_H
#define SCRAPER_RESOURCE_H

#include "request.h"

typedef struct Resource {
    Request *pRequest;
    char *outputPath;
    char *type;
    int depth;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} Resource;

#endif //SCRAPER_RESOURCE_H