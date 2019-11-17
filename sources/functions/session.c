/*
 *  Filename    : session.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#include "../headers/session.h"

static int setSession(Session *pSession, Action *action);
static void initAndSetResource(Session *pSession, Action *pAction);

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

    if (setSession(pSession, action)) {
        free(pSession);
        return NULL;
    }
    pSession->nameAction = strMallocCpy(action->name, (int)strlen(action->name));

    initAndSetResource(pSession, action);

    return pSession;
}

static int setSession(Session *pSession, Action *action) {
    pSession->nameAction = strMallocCpy(action->name, strlen(action->name));
    if (pSession->nameAction == NULL) {
        fprintf(stderr, "Problem strMallocCpy pSession->nameAction\n");
        return 0;
    }

    pSession->createdDate = getCurrentTime();
    if (pSession->)
}

static void initAndSetResource(Session *pSession, Action *pAction) {




    //pSession->resources = initResource(action->url, ) TODO : get depth of action
//    if (pSession->resources == NULL) {
//        fprintf(stderr, "Problem of malloc resources for pointer of Session\n");
//        exit(1);
//    }
}

// addResourceRecursively(url, maxDepth)

// checkIfResourceExist(url)

void buildSessionInProject(Session *pSession) {

}

void destroySession(Session *pSession) {

}