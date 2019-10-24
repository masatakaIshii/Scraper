//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_SESSION_H
#define SCRAPER_SESSION_H


#include "action.h"
#include "resource.h"

typedef struct Session {
    Action *action;
    Resource **rawResources;
    char *name;
    int numberResources;
    char *createdDate;
    int maxDepth;
    int isVersioning;
    char **types;
} Session;



#endif //SCRAPER_SESSION_H
