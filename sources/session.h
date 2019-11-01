/*
 *  Filename    : session.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#ifndef SCRAPER_SESSION_H
#define SCRAPER_SESSION_H

#include "common.h"
#include "action.h"
#include "resource.h"

typedef struct Session {
    Action **actions;
    int numberActions;
    char *name;
    Resource **resources;
    char *createdDate;
} Session;

Session *initSession(Action *action, char *sessionName);

void destroySession(Session *pSession);

#include "app.h"

#endif //SCRAPER_SESSION_H
