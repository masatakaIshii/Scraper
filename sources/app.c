/*
 *  Filename    : app.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage app structure and functions to init, start and quit Scraper
 */

#include "app.h"

/**
 * function to get singleton pointer App structure
 * @return App* pApp : pointer of app structure
 */
App *getApp() {
    static App *pApp = NULL;

    if (pApp == NULL) {
        pApp = malloc(sizeof(App));
        pApp->pConfig = NULL;
        pApp->listSession = newListSession();
    }

    return pApp;
}

/**
 * Function to init list of sessions
 * @return listSession : list of sessions
 */
ListSession *newListSession() {
    ListSession *listSession = malloc(sizeof(ListSession));
    if (listSession == NULL) {
        return NULL;
    }
    listSession->capacity = 10;

    listSession->sessions = malloc(sizeof(Session*) * listSession->capacity);
    if (listSession->sessions == NULL) {
        free(listSession);
        return NULL;
    }

    return listSession;
}


void freeListSession(ListSession *pSession) {
    int i;

    for (i = 0; i < pSession->count; i++) {
        destroySession(pSession->sessions[i]);
    }
    free(pSession->sessions);
    free(pSession);
}

int sessionsCount() {
    App *pApp = getApp();
    return pApp->listSession->count;
}


void addSession(Session *pSession) {
    App *pApp = getApp();

    // TODO
}

Session *getSession(int index) {
    // TODO
}

/**
 * function get config with structure App
 * @return
 */
Config *getConfig() {

}

/**
 * destroy singleton of pointer of structure App
 * @param pApp : pointer of structure App
 */
void destroyApp() {
    App *pApp = getApp();

    if (pApp->pConfig != NULL) {
        free(pApp->pConfig);
        pApp->pConfig = NULL;
    }

    if (pApp->listSession != NULL) {
        freeListSession(pApp->listSession);
        pApp->listSession = NULL;
    }

    free(pApp);
}
