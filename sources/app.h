/*
 *  Filename    : app.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage app structure and functions to init, start and quit Scraper
 */

#ifndef SCRAPER_APP_H
#define SCRAPER_APP_H

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "session.h"

typedef struct App {
    Config *pConfig;
    int numberSession;
    Session **pSessions;
} App;

App *getApp();

// TODO: Config *getConfig

// TODO: Session *getSession

// TODO: void destroyApp(App *pApp);

// TODO: int startApp(App *app);

#endif //SCRAPER_APP_H