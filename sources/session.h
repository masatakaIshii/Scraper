/*
 *  Filename    : session.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#ifndef SCRAPER_SESSION_H
#define SCRAPER_SESSION_H

#include "app.h"
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

Session *initSession(Action *action);


#endif //SCRAPER_SESSION_H
