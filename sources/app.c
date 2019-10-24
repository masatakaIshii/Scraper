/*
 *  Filename    : app.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage app structure and functions to init, start and quit Scraper
 */

#include "app.h"

App *getApp() {
    static App *pApp = NULL;

    if (pApp == NULL) {
        pApp = malloc(sizeof(App));
        pApp->numberSession = 0;
        pApp->pConfig = NULL;
    }

    return pApp;
}