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

int getCountListMimeType() {

}

char **getListMimeTypeFileExt() {

}

char *getFileNameByUrl(char *url, char *mimeType) {

}