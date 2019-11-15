//
// Created by masat on 15/11/2019.
//

#ifndef SCRAPER_MYSTRING_H
#define SCRAPER_MYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListChar {
    char *content;
    int capacity;
    int count;
    int mul;
} String;

String *initString(int capacity, int mul);

int addString(String *pString, char *strToAdd);

void destroyString(String *pString);

#endif //SCRAPER_MYSTRING_H
