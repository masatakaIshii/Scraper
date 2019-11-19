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
#include "request.h"
#include "resource.h"

Session *initSession(Action *action, char *nameTask);

int runSessionAndResources(Session *pSession, Action *pAction);

void destroySession(Session *pSession);

#endif //SCRAPER_SESSION_H
