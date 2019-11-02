/*
 *  Filename    : common.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#ifndef SCRAPER_COMMON_H
#define SCRAPER_COMMON_H
#include <curl/curl.h>
#include "struct.h"
#include "app.h"


void verifyPointer(void *pointer, const char *message);

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return
 */
char *strMallocCpy(const char *str, int length);

/**
 * get index of array of char strCheck after the occurrence of string strOccur
 * @param strCheck : string to search if there are occurrence
 * @param strOccur : string correspond to occurrence
 * @return index : index after occurrence strOccur
 */
int getIndexAfterOccurStr(const char *strCheck, const char *strOccur);

/**
 * Get current time format "strDate strMonth intDate intHours:intMin:intSec intYears"
 * Example : "Sun Oct 01 13:12:00 2019"
 * @return string content current time
 */
char *getCurrentTime();

char *strMallocCat(const char *str1, const char *str2);

//int getCountListMimeType();
//
//char **getListMimeTypeFileExt();
//
//char *getFileNameByUrl(char *url, char *mimeType);

#endif //SCRAPER_COMMON_H
