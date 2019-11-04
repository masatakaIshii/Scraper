/*
 *  Filename    : common.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#include "common.h"

/**
 * verify the pointer and if its null, show message and quit program with exit status '1'
 * @param pointer
 * @param message
 */
void verifyPointer(void *pointer, const char *message) {
    if (pointer == NULL) {
        destroyApp();
        fprintf(stderr, "%s", message);
        curl_global_cleanup();
        exit(1);
    }
}

/**
 * strcat with proper malloc and not static array of character
 * @param str1
 * @param str2
 * @return newStr : string that is concat with str1 and str2
 */
char *strMallocCat(const char *str1, const char *str2) {
    char *newStr = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
    if (newStr == NULL) {
        return NULL;
    }

    strcpy(newStr, str1);
    strcat(newStr, str2);

    return newStr;
}

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return newStr : new string that is malloc
 */
char *strMallocCpy(const char *str, int length) {
    char *newStr = calloc(length + 1, sizeof(char));
    if (newStr == NULL) {
        return NULL;
    }

    strncpy(newStr, str, length);
    return newStr;
}

/**
 * get index of array of char strCheck after the occurrence of string strOccur
 * @param strCheck : string to search if there are occurrence
 * @param strOccur : string correspond to occurrence
 * @return index : index after occurrence strOccur
 */
int getIndexAfterOccurStr(const char *strCheck, const char *strOccur) {
    char *startOccur = strstr(strCheck, strOccur);

    if (startOccur != NULL) {
        return startOccur - strCheck + strlen(strOccur);
    }

    return 0;
}

/**
 * Get current time format "strDate strMonth intDate intHours:intMin:intSec intYears"
 * Example : "Sun Oct 01 13:12:00 2019"
 * @return string content current time
 */
char *getCurrentTime() {
    time_t currentTime;
    char *strCurrentTime = NULL;

    currentTime = time(NULL);
    if (currentTime == (time_t) - 1) {
        return NULL;
    }

    strCurrentTime = ctime(&currentTime);

    return strCurrentTime;
}

/**
 * destroy pointer if boolean of field is == 1, and affect boolean to 0
 * @param pointer : the pointer to free
 * @param isMalloc : variable of boolean to check if pointer is already malloc and put to 0
 */
void freePointer(void **pointer, int *isMalloc) {
    if (*isMalloc == 1) {
        free(*pointer);
        *pointer = NULL;
        *isMalloc = 0;
    }
}

//
//int getCountListMimeType() {
//
//}
//
//char **getListMimeTypeFileExt() {
//
//}
//
//char *getFileNameByUrl(char *url, char *mimeType) {
//
//}