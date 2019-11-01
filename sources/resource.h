//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RESOURCE_H
#define SCRAPER_RESOURCE_H

#include "common.h"
#include "request.h"

typedef struct Resource {
    Request *pRequest;
    char *dirResourcePath;
    char *outputPath;
    char *type;
    int depth;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} Resource;

Resource *initResource(const char *url, int depth, int maxDepth);

int createFileResource(Resource *pResource, const char *dirResourcePath);

void addResourceInformationInResourcesFile(Resource *pResource, const char *resourcesFile);

#endif //SCRAPER_RESOURCE_H