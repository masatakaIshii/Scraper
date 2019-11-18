////
//// Created by masat on 01/11/2019.
////
//
//#include "testDummiesAction.h"
//
//Action *dummySimpleAction() {
//    Action *pAction = malloc(sizeof(Action));
//    if (pAction == NULL) {
//        fprintf(stderr, "Probleme malloc structure Action in dummyAction()\n");
//        exit(1);
//    }
//    pAction->url = "http://yahoo.com";
//    pAction->name = "first action";
//    pAction->numberOption = 1;
//    pAction->options = malloc(sizeof(Option*) * pAction->numberOption);
//    if (pAction->options == NULL) {
//        fprintf(stderr, "Problem malloc list of ");
//    }
//    pAction->options[0] = malloc(sizeof(Option));
//    pAction->options[0]->name = strMallocCpy("max-depth", strlen("max-depth"));
//    pAction->options[0]->typeValue = OPTION_INT;
//    pAction->options[0]->nbrValue = 1;
//    pAction->options[0]->value.valueInt = 0;
//
//    return pAction;
//}
//
//void destroyDummyAction(Action *dummyAction) {
//    int i;
//    int j;
//    for (i = 0; i < dummyAction->numberOption; i++) {
//        if (dummyAction->options[i]->typeValue == OPTION_LIST_STR) {
//            for (j = 0; j < dummyAction->options[i]->nbrValue; j++) {
//                free(dummyAction->options[i]->value.listStr[i]);
//            }
//        }
//        if (dummyAction->options[i]->typeValue == OPTION_STR) {
//            free(dummyAction->options[i]->value.valueStr);
//        }
//    }
//
//    free(dummyAction->options);
//    free(dummyAction);
//}
//
//Action *dummyDepthAction() {
//    Action *pAction = malloc(sizeof(Action));
//    if (pAction == NULL) {
//        fprintf(stderr, "Probleme malloc structure Action in dummyAction()\n");
//        exit(1);
//    }
//    pAction->url = "http://yahoo.com";
//    pAction->name = "first action";
//    pAction->numberOption = 3;
//    pAction->options = malloc(sizeof(Option*) * pAction->numberOption);
//    if (pAction->options == NULL) {
//        fprintf(stderr, "Problem malloc list of options");
//    }
//    pAction->options[0]->name = "max-depth";
//    pAction->options[0]->nbrValue = 1;
//    pAction->options[0]->typeValue = OPTION_INT;
//    pAction->options[0]->value.valueInt = 1;
//
//    pAction->options[1]->name = "versioning";
//    pAction->options[1]->nbrValue = 1;
//    pAction->options[1]->typeValue = OPTION_INT;
//    pAction->options[1]->value.valueInt = 0;
//
//    pAction->options[2]->name = "type";
//    pAction->options[2]->nbrValue = 1;
//    pAction->options[2]->typeValue = OPTION_STR;
//    pAction->options[2]->value.valueStr = "text/html";
//
//    return pAction;
//}
