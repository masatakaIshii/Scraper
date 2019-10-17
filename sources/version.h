//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_VERSION_H
#define SCRAPER_VERSION_H

#include "task.h"

typedef struct Version {
    Action *action;
    Task *task;
    char *date;
    char *currentPath;
} Version;

#endif //SCRAPER_VERSION_H
