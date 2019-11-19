//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RESOURCE_H
#define SCRAPER_RESOURCE_H

#include <io.h>
#include "common.h"
#include "request.h"
#include "../headers/urlSearcher.h"

Resource *initResource(const char *url, Action *pAction, int depth);

int setTypesFilter(Resource *pResource, char **types, int count);

int createFileResource(Resource **pResource, const char *dirResourcePath, Action *pAction, int depth);

void addResourceInformationInResourcesFile(Resource *pResource, const char *resourcesFile);

void destroyResource(Resource *pResource);

#endif //SCRAPER_RESOURCE_H