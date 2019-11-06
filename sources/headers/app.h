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
#include "request.h"
#include "session.h"

/**
 * function to get singleton pointer App structure
 * @return App* pApp : pointer of app structure
 */
App *getApp();


// ----- ListSession functions -----
/**
 * Function to init list of sessions
 * @return listSession : list of sessions
 */
ListSession *newListSession();

void addSession(Session *pSession);

Session *getSession(int index);

void freeListSession(ListSession *pSession);

/**
 * function to get
 * @return
 */
Config *getConfig();
// TODO: Config *getConfig

// TODO: Session *getSession



void destroyApp();



// TODO: int startApp(App *app);

#endif //SCRAPER_APP_H