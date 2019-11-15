/*
 *  Filename    : listChar.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : create list of character to manage adding string and expanding capacity
 */

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

/**
 * Init the structure String that contain expandable string
 * @param capacity : initial capacity of content
 * @param mul : when string to add to content exceed the capacity, expand it with mul the value
 * @return OK pString : pointer of structure String that is init, <br>
 * ERROR NULL : the reason can be problem of malloc or the incorrect values of capacity and|or mull
 */
String *initString(int capacity, double mul);

/**
 * Add string in content of structure String
 * @param pString : pointer of structure String
 * @param strToAdd : string to add in structure
 * @return OK 1 : the string is add in structure, <br>
 * ERROR 0 : fail to add string, pString memory is free
 */
int addString(String *pString, const char *strToAdd);

/**
 * Free content and structure of String
 * @param pString : pointer of structure String
 */
void destroyString(String *pString);

#endif //SCRAPER_LISTCHAR_H
