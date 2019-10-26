/*
 *  Filename    : session.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#ifndef SCRAPER_SESSION_H
#define SCRAPER_SESSION_H

#include "action.h"
#include "resource.h"

typedef struct Session {
    Action *action;
    char *fileName;
    Resource **rawResources;
    int numberResources;
    char *createdDate;
    int maxDepth;
    int isVersioning;
    char **types; // ?
} Session;

Session *initSession(Action *action);

#include "app.h"

#endif //SCRAPER_SESSION_H
