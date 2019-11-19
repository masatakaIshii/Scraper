////
//// Created by masat on 01/11/2019.
////

#include "testDummiesAction.h"

void initDummyAction(Action *pAction) {
    pAction->url = NULL;
    pAction->name = NULL;
    pAction->types = NULL;
    pAction->numberTypes = 0;
    pAction->maxDepth = 0;
    pAction->versioning = 0;
}

Action *dummySimpleAction() {
    Action *pAction = malloc(sizeof(Action));
    if (pAction == NULL) {
        fprintf(stderr, "Probleme malloc structure Action in dummyAction()\n");
        exit(1);
    }
    initDummyAction(pAction);

    pAction->url = strMallocCpy("http://yahoo.com", strlen("http://yahoo.com"));

    pAction->name = strMallocCpy("first action", strlen("first action"));

    return pAction;
}

Action *dummyTypesAction() {
    int i;
    char *types[100] = {"text/html", "application/javascript", "text/css"};
    Action *pAction = malloc(sizeof(Action));
    if (pAction == NULL) {
        fprintf(stderr, "Probleme malloc structure Action in dummyAction()\n");
        exit(1);
    }
    initDummyAction(pAction);

    pAction->url = strMallocCpy("http://yahoo.com", strlen("http://yahoo.com"));
    pAction->name = strMallocCpy("first action", strlen("first action"));
    pAction->numberTypes = 3;
    pAction->maxDepth = 1;

    pAction->types = malloc(sizeof(char *) * pAction->numberTypes);
    for (i = 0; i < pAction->numberTypes; i++) {
        pAction->types[i] = strMallocCpy(types[i], strlen(types[i]));
    }
    return pAction;
}

Action *dummyDepthAction() {
    Action *pAction = malloc(sizeof(Action));
    if (pAction == NULL) {
        fprintf(stderr, "Probleme malloc structure Action in dummyAction()\n");
        exit(1);
    }
    pAction->url = strMallocCpy("http://www.example.com", strlen("http://www.example.com"));
    pAction->name = strMallocCpy("depth action", strlen("depth action"));
    pAction->versioning = 1;
    pAction->maxDepth = 1;

    return pAction;
}


void destroyDummyAction(Action *dummyAction) {
    if (dummyAction->numberTypes > 0) {
        freeArrayString(dummyAction->types, dummyAction->numberTypes);
    }
    if (dummyAction->url != NULL) {
        free(dummyAction->url);
    }
    if (dummyAction->name != NULL) {
        free(dummyAction->name);
    }
    free(dummyAction);
}