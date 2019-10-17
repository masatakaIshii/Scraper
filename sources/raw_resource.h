//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RAW_RESOURCE_H
#define SCRAPER_RAW_RESOURCE_H

typedef struct RawResource {
    char *fileName;
    char *rawPath;
    char *outputPath;
    char *type;
    int depth;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} RawResource;

#endif //SCRAPER_RAW_RESOURCE_H
