//
// Created by masat on 12/11/2019.
//

#include "../headers/listArray.h"

static int expandListStrCapacity(ListStr *listStr);

ListStr *initListStr(int stepCapacity) {
    ListStr *listStr = malloc(sizeof(ListStr));
    if (listStr == NULL) {
        return NULL;
    }
    listStr->capacity = stepCapacity;
    listStr->count = 0;
    listStr->arrStr = malloc(sizeof(char *) * listStr->capacity);
    if (listStr->arrStr == NULL) {
        free(listStr);
        return NULL;
    }

    return listStr;
}

int listStrAdd(ListStr *listStr, const char *strToAdd) {

    if (listStr->count == listStr->capacity) {
        if (expandListStrCapacity(listStr) == 0) {
            destroyListStr(listStr);
            return 0;
        }
    }

    listStr->arrStr[listStr->count] = calloc(strlen(strToAdd) + 1, sizeof(char));
    if (listStr->arrStr[listStr->count] == NULL) {
        destroyListStr(listStr);
        return 0;
    }

    strcpy(listStr->arrStr[listStr->count], strToAdd);

    listStr->count++;
    return 1;
}

static int expandListStrCapacity(ListStr *listStr) {
    int i;
    char **newArrStr = NULL;

    listStr->capacity *= 2;
    newArrStr = malloc(sizeof(char*) * listStr->capacity);
    if (newArrStr == NULL) {
        destroyListStr(listStr);
        return 0;
    }
    for (i = 0; i < listStr->count; i++) {
        newArrStr[i] = calloc(strlen(listStr->arrStr[i]) + 1, sizeof(char));
        if (newArrStr[i] == NULL) {
            freeArrayString(newArrStr, i);
            destroyListStr(listStr);
            return 0;
        }
        strcpy(newArrStr[i], listStr->arrStr[i]);
    }
    free(listStr->arrStr);
    listStr->arrStr = newArrStr;

    return 1;
}

const char* listStrGet(ListStr *listStr, int index) {
    //char *string = calloc(strlen(listStr->arrStr[index]), sizeof(char));
    return listStr->arrStr[index];
}

void destroyListStr(ListStr *ListStr) {
    int i;

    for (i = 0; i < ListStr->count; i++) {
        free(ListStr->arrStr[i]);
    }
    free(ListStr->arrStr);
    free(ListStr);
}
