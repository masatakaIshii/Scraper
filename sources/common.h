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

void errorQuit(char *message);

char *strMallocCpy(const char *str, int length);

int getIndexAfterOccurStr(const char *strCheck, const char *strOccur);

char *getCurrentTime();

char *strMallocCat(const char *str1, const char *str2);

int getCountListMimeType();

char **getListMimeTypeFileExt();

char *getFileNameByUrl(char *url, char *mimeType);

#endif //SCRAPER_COMMON_H
