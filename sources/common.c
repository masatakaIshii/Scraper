/*
 *  Filename    : common.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#include "common.h"

void errorQuit(char *message) {
    printf("%s", message);
    curl_global_cleanup();
    exit(1);
}

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return
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
        //destroyApp();
        return NULL;
    }

    strCurrentTime = ctime(&currentTime);

    return strCurrentTime;
}

char *strMallocCat(const char *str1, const char *str2) {
    char *newStr = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
    if (newStr == NULL) {
        //destroyApp();
        errorQuit("Problem to calloc string in strMallocCat");
    }

    strcpy(newStr, str1);
    strcat(newStr, str2);

    return newStr;
}

int getCountListMimeType() {

}

char **getListMimeTypeFileExt() {

}

char *getFileNameByUrl(char *url, char *mimeType) {

}