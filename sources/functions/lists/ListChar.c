/*
 *  Filename    : listChar.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : create list of character to manage adding string and expanding capacity
 */

#include "../../headers/lists/ListChar.h"

static char *expandStringContent(String *pString);

/**
 * Init the structure String that contain expandable string
 * @param capacity : initial capacity of content
 * @param mul : when string to add to content exceed the capacity, expand it with mul the value
 * @return OK pString : pointer of structure String that is init, <br>
 * ERROR NULL : the reason can be problem of malloc or the incorrect values of capacity and|or mull
 */
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

/**
 * Add string in content of structure String
 * @param pString : pointer of structure String
 * @param strToAdd : string to add in structure
 * @return OK 1 : the string is add in structure, <br>
 * ERROR 0 : fail to add string, pString memory is free
 */
int addString(String *pString, const char *strToAdd) {
    int lengthStr = (int)strlen(strToAdd);

    while (pString->capacity < lengthStr + pString->count + 1) {
        pString->content = expandStringContent(pString);
        if (pString->content == NULL) {
            fprintf(stderr, "ERROR in addString : fail to expand content of pString\n");
            free(pString);
            return 0;
        }
    }
    strcat(pString->content, strToAdd);
    pString->count += lengthStr;

    return 1;
}

/**
 * Expand the capacity of structure String
 * @param pString : pointer of structure String
 * @return OK newContent : the string with more memory allocation, <br>
 * ERROR NULL : fail to memory allocate
 */
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

/**
 * Free content and structure of String
 * @param pString : pointer of structure String
 */
void destroyString(String *pString) {

    free(pString->content);
    free(pString);
}