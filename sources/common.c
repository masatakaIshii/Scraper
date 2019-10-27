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
 * @param strCheck
 * @param strOccur
 * @return index : index after occurrence strOccur
 */
int getIndexAfterOccurStr(const char *strCheck, const char *strOccur) {
    char *startOccur = strstr(strCheck, strOccur);

    if (startOccur != NULL) {
        return startOccur - strCheck + strlen(strOccur);
    }

    return 0;
}

int getCountListMimeType() {

}

char **getListMimeTypeFileExt() {

}

char *getFileNameByUrl(char *url, char *mimeType) {

}