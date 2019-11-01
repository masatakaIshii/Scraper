/*
 *  Filename    : session.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#include "session.h"

Session *initSession(Action *action, char *sessionName) {
    Session *pSession = malloc(sizeof(Session));
    if (pSession == NULL) {
        fprintf(stderr, "Problem malloc pointer of Session\n");
        exit(1);
    }
    if (action != NULL) {
        free(pSession);
        return NULL;
    }
    //pSession->actions = malloc(sizeof(Action*));

    pSession->createdDate = getCurrentTime();
    pSession->resources = malloc(sizeof(Resource*));
    if (pSession->resources == NULL) {
        fprintf(stderr, "Problem of malloc resources for pointer of Session\n");
        exit(1);
    }

    return pSession;
}

void buildSessionInProject(Session *pSession) {

}

void destroySession(Session *pSession) {

}