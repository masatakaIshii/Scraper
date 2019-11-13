//
// Created by masat on 12/11/2019.
//

#ifndef SCRAPER_LISTARRAY_H
#define SCRAPER_LISTARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/common.h"

typedef struct ListString {
    char **arrStr;
    int capacity;
    int count;
} ListStr;

ListStr *initListStr(int initCapacity);

int listStrAdd(ListStr *ListStr, const char *strToAdd);

const char* listStrGet(ListStr *listStr, int index);

void destroyListStr(ListStr *listStr);

#endif //SCRAPER_LISTARRAY_H
