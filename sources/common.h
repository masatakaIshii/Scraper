/*
 *  Filename    : common.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#ifndef SCRAPER_COMMON_H
#define SCRAPER_COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>

enum UrlHelperResponse {
    UH_WITH_FILE_EXT,
    UH_WITHOUT_FILE_EXT,
    UH_NAME_PB,
    UH_MEM_PB
};

void errorQuit(char *message);

int haveFileExt(char *url);

int getCountListMimeType();

char **getListMimeTypeFileExt();

char *getFileNameByUrl(char *url, char *mimeType);

#include "app.h"

#endif //SCRAPER_COMMON_H
