//
// Created by masat on 15/11/2019.
//

#include "../../headers/lists/ListChar.h"

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

    pString->content = calloc(pString->capacity, sizeof(char));
    if (pString->content == NULL) {
        fprintf(stderr, ("Problem calloc pString->content in initString\n"));
        free(pString);
        return NULL;
    }

    return pString;
}

int addString(String *pString, char *strToAdd) {
    return 0;
}

void destroyString(String *pString) {

    free(pString->content);
    free(pString);
}