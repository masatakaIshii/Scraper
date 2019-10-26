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

void errorQuit(char *message);

int getCountListMimeType();

char **getListMimeTypeFileExt();

char *getFileNameByUrl(char *url, char *mimeType);

#endif //SCRAPER_COMMON_H
