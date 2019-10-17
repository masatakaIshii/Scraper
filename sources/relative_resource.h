//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RELATIVE_RESOURCE_H
#define SCRAPER_RELATIVE_RESOURCE_H

#include "raw_resource.h"

typedef struct RelativeResource {
    char *fileName;
    char *relativePath;
    char *createdDate;
    RawResource *rawResource;
} RelativeResource;

#endif //SCRAPER_RELATIVE_RESOURCE_H
