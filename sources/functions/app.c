/*
 *  Filename    : app.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage app structure and functions to init, start and quit Scraper
 */

#include "../headers/app.h"

/**
 * function to get singleton pointer App structure
 * @return App* pApp : pointer of app structure
 */
App *initApp() {
    App *pApp = NULL;

    pApp = malloc(sizeof(App));
    if (pApp == NULL) {
        return NULL;
    }

    pApp->pConfig = NULL;
    pApp->session = NULL;

    return pApp;
}

int runApp(App *pApp) {

    pApp->pConfig = initConfig();

    if (fillConfig(pApp->pConfig) != 0) {
        destroyConfig(pApp->pConfig);
        return 1;
    }

    return 0;
    // TODO : boucle pour lancer session
}

/**
 * destroy singleton of pointer of structure App
 * @param pApp : pointer of structure App
 */
void destroyApp() {

//    if (pApp->pConfig != NULL) {
//        //destroyConfig(App->pConfig); TODO: do destroyConfig
//        pApp->pConfig = NULL;
//    }
//
//    if (pApp->session != NULL) {
//        destroySession(pApp->session);
//        pApp->session = NULL;
//    }
//
//    free(pApp);
}
