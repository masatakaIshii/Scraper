//
// Created by masat on 15/11/2019.
//

#ifndef SCRAPER_LISTCHAR_H
#define SCRAPER_LISTCHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListChar {
    char *content;
    int capacity;
    int count;
    double mul;
} String;

String *initString(int capacity, double mul);

int addString(String *pString, char *strToAdd);

void destroyString(String *pString);

#endif //SCRAPER_LISTCHAR_H
