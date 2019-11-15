//
// Created by masat on 15/11/2019.
//

#include "../../headers/lists/ListChar.h"

static char *expandStringContent(String *pString);

String *initString(int capacity, double mul) {
    String *pString;

    if (capacity <= 0 || mul <= 1) {
        return NULL;
    }

    pString = malloc(sizeof(String));
    if (pString == NULL) {
        fprintf(stderr, ("Problem malloc pString in initString\n"));
        return NULL;
    }

    pString->capacity = capacity;
    pString->mul = mul;
    pString->count = 0;

    pString->content = calloc(pString->capacity, sizeof(char));
    if (pString->content == NULL) {
        fprintf(stderr, ("Problem calloc pString->content in initString\n"));
        free(pString);
        return NULL;
    }

    return pString;
}

int addString(String *pString, const char *strToAdd) {
    int lengthStr = (int)strlen(strToAdd);

    while (pString->capacity < lengthStr + pString->count + 1) {
        pString->content = expandStringContent(pString);
        if (pString->content == NULL) {
            free(pString);
            return 0;
        }
    }
    strcat(pString->content, strToAdd);
    pString->count = lengthStr;

    return 1;
}

static char *expandStringContent(String *pString) {
    char *newContent = NULL;

    pString->capacity = (int)(pString->capacity * pString->mul);

    newContent = calloc(pString->capacity, sizeof(char));
    if (newContent == NULL) {
        fprintf(stderr, "ERROR in ListChar : Problem calloc newContent in function expandStringContent\n");
    } else {
        strcpy(newContent, pString->content);
    }
    free(pString->content);

    return newContent;
}

void destroyString(String *pString) {

    free(pString->content);
    free(pString);
}