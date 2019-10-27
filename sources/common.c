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

int haveFileExt(char *url) {
    int length = 0;
    char *withoutProtocolCom = NULL;
    char *checkSlash = NULL;
    char *checkPoint =  NULL;
    int result = UH_NAME_PB;

    if ((length = strspn(url, "https://")) == strlen("https://") ||
        (length = strspn(url, "http://")) == strlen("http://")) {
        result = UH_WITHOUT_FILE_EXT;

        withoutProtocolCom = url + length;
        if (withoutProtocolCom != NULL) {
            checkSlash = strrchr(withoutProtocolCom, '/');
            if (checkSlash != NULL) {
                checkPoint = strrchr(checkSlash, '.');
                if (checkPoint != NULL) {
                    result = UH_WITH_FILE_EXT;
                }
            }
        }
    }

    return result;
}

int getCountListMimeType() {

}

char **getListMimeTypeFileExt() {

}

char *getFileNameByUrl(char *url, char *mimeType) {

}