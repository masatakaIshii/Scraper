//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_RESOURCE_H
#define SCRAPER_RESOURCE_H

typedef struct Resource {
    char *fileName;
    char *rawPath;
    char *outputPath;
    char *type;
    int depth;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} Resource;

#endif //SCRAPER_RESOURCE_H
