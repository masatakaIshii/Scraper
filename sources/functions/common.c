/*
 *  Filename    : common.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#include "../headers/common.h"

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
        return (int)(startOccur - strCheck + strlen(strOccur));
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
    char *temp = NULL;

    currentTime = time(NULL);
    if (currentTime == (time_t) - 1) {
        return NULL;
    }

    temp = ctime(&currentTime);
    strCurrentTime = strMallocCpy(temp, (int)strlen(temp));

    verifyPointer(strCurrentTime, "Problem get current time\n");

    return strCurrentTime;
}

/**
 * destroy pointer if boolean of field is == 1, and affect boolean to 0
 * @param pointer : the pointer to free
 * @param isMalloc : variable of boolean to check if pointer is already malloc and put to 0
 */
void freePointer(void **pointer, short *isMalloc) {
    if (*isMalloc == 1) {
        free(*pointer);
        *pointer = NULL;
        *isMalloc = 0;
    }
}

/**
 * Check if directory path is correct
 * DEBT : the backslash is include in forbidden chars because the function below depend to mkdirP
 * @param dirPath
 * @return
 * 1 : dirPath is correct
 * 0 : dirPath contain forbidden Chars
 */
static int checkIfDirPathIsCorrect(char *dirPath) {
    char *arrayForbiddenChars = "\\<>?\":*|";

    return strpbrk(dirPath, arrayForbiddenChars) == NULL;
}

/**
 * function to create directories step by step thanks to token
 * @param dirPath
 * @return
 * 0 : operation success
 * -1 : problem with token
 */
static int  createDirectories(const char *dirPath) {
    const char s[2] = "/";
    unsigned length = strlen(dirPath);
    char temp[length];
    char currentDirPath[length];
    char *token;

    strcpy(temp, dirPath);
    token = strtok(temp, s);
    if (token == NULL) {
        return -1;
    }

    strcpy(currentDirPath, token);
    while( token != NULL) {
        mkdir(currentDirPath);
        token = strtok(NULL, s);
        if (token != NULL) {
            strcat(currentDirPath, "/");
            strcat(currentDirPath, token);
        }
    }
    return 0;
}

/**
 * function to create directories recursively like mkdirP
 * @param dirPath
 * @return
 * 0 : correct value and directories created
 * -1 : error value, because of directory path wrong value
 */
int mkdirP(char *dirPath) {

    if (checkIfDirPathIsCorrect(dirPath) == 0) {
        return -1;
    }

    return createDirectories(dirPath);
}

/**
 * Function to verify if the directory exist
 * @param dirPath
 * @return
 * 1 : directory that have dirPath value exist
 * 0 : directory that is dirPath not exist
 */
int checkIfDirExist(char *dirPath) {
    DIR *dir = opendir(dirPath);
    if (dir) {
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        return 0;
    } else {
        fprintf(stderr, "Problem to open dir : %s\n", dirPath);
        return 0;
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