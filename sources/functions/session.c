/*
 *  Filename    : session.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#include "../headers/session.h"

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
    pSession->resources = initResource(action->url, action->)
    if (pSession->resources == NULL) {
        fprintf(stderr, "Problem of malloc resources for pointer of Session\n");
        exit(1);
    }

    pSession

    return pSession;
}

// addResourceRecursively(url, maxDepth)

// checkIfResourceExist(url)

void buildSessionInProject(Session *pSession) {

}

void destroySession(Session *pSession) {

}