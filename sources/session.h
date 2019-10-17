//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_SESSION_H
#define SCRAPER_SESSION_H


#include "action.h"
#include "raw_resource.h"
#include "relative_resource.h"

typedef struct Session {
    Action *action;
    RawResource **rawResources;
    int nbrRawResources;
    RelativeResource **relativeResources;
    int nbrRelativeResources;
    char *createdDate;
    int maxDepth;
    int isVersioning;
    char **types;
} Session;

#endif //SCRAPER_SESSION_H
