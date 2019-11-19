/*
 *  Filename    : session.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : file to manage the session of action
 */

#include "../headers/session.h"

static void initValuesSession(Session *pSession);
static int setSession(Session *pSession, Action *action, char *nameTask);

Session *initSession(Action *action, char *nameTask) {
    Session *pSession = malloc(sizeof(Session));
    if (pSession == NULL) {
        fprintf(stderr, "Problem malloc pointer of Session\n");
        exit(1);
    }
    if (action == NULL) {
        free(pSession);
        return NULL;
    }
    initValuesSession(pSession);

    if (setSession(pSession, action, nameTask) == 0) {
        destroySession(pSession);
        return NULL;
    }

    return pSession;
}

static void initValuesSession(Session *pSession) {
    pSession->createdDate = NULL;
    pSession->dateSeconds = 0;
    pSession->resources = NULL;
    pSession->taskName = NULL;
    pSession->actionName = NULL;
    pSession->sessionDirPath = NULL;
}

static int setSession(Session *pSession, Action *action, char *nameTask) {
    pSession->actionName = strMallocCpy(action->name, strlen(action->name));
    if (pSession->actionName == NULL) {
        fprintf(stderr, "Problem strMallocCpy pSession->actionName\n");
        return 0;
    }
    pSession->taskName = strMallocCpy(nameTask, strlen(nameTask));
    if (pSession->taskName == NULL) {
        fprintf(stderr, "ERROR in setSession : Problem strMallocCpy pSession->taskName\n");
        return 0;
    }

    pSession->dateSeconds = getCurrentTimeSec();
    if (pSession->dateSeconds <= 0) {
        fprintf(stderr, "Error in setSession : Problem getCurrentTimeSec\n");
        return 0;
    }
    pSession->createdDate = getTimeToString(pSession->dateSeconds);
    if (pSession->createdDate == NULL) {
        fprintf(stderr, "Error in setSession : Problem getTimeToString\n");
        return 0;
    }

    return 1;
}

static char *getSessionDirPath(int versioning, char *actionName) {
    char *sessionDirPath = NULL;

    if (versioning == 1) {
        // check if sessionDirPath directory exist
    } else {
        sessionDirPath = getAvailableName("session_all_names.txt", "Scraper", "Scraper/session", "_");
        if (sessionDirPath == NULL) {
            fprintf(stderr, "ERROR in runSessionAndResources : Problem get session name\n");
            return 0;
        }
    }

    return sessionDirPath;
}

/**
 * Run session and get resources by action
 * @param pSession
 * @param pAction
 * @return OK 1,<br>
 * ERROR 0
 */
int runSessionAndResources(Session *pSession, Action *pAction) {
    pSession->sessionDirPath = getSessionDirPath(pAction->versioning, pAction->name);
    if (pSession->sessionDirPath == NULL) {
        fprintf(stderr, "ERROR in runSessionAndResources : problem to get session dir path\n");
        return 0;
    }

    // init resource and save initSession

    return 1;
}

void buildSessionInProject(Session *pSession) {

}

void destroySession(Session *pSession) {
    if (pSession->actionName != NULL) {
        free(pSession->actionName);
    }

    if (pSession->taskName != NULL) {
        free(pSession->taskName);
    }

    if (pSession->createdDate != NULL) {
        free(pSession->createdDate);
    }

    if (pSession->resources != NULL) {
        destroyResource(pSession->resources);
    }
    free(pSession);
}