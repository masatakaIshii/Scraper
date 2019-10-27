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

char *getFileName(const char *resourceUrl, int length) {
    char *fileName = NULL;

    fileName = calloc(length, sizeof(char));
    if (fileName == NULL) {
        return NULL;
    }
    strncpy(fileName, resourceUrl, length - 1);

    return fileName;
}

UHRes searchAfterComProtocol(char *urlWithoutComProtocol, char **fileName) {
    UHRes result = UH_WITHOUT_FILE_EXT;
    int length = 0;
    char *urlResource = NULL;
    char *checkPoint = NULL;

    if (urlWithoutComProtocol != NULL) {
        urlResource = strrchr(urlWithoutComProtocol, '/');
        if (urlResource != NULL) {
            length = strrchr(urlResource, '?') != NULL ? strrchr(urlResource, '?') - urlResource + 1 : strlen(urlResource) + 1;
            urlResource = getFileName(urlResource, length);
            checkPoint = strrchr(urlResource, '.');
            if (checkPoint != NULL) {
                result = UH_WITH_FILE_EXT;
            }
            if (fileName != NULL) {
                *fileName = urlResource;
                if (*fileName == NULL) {
                    result = UH_MEM_PB;
                }
            } else {
                free(urlResource);
            }
        }
    }

    return result;
}

UHRes haveFileExt(char *url, char **fileName) {
    UHRes result = UH_NAME_PB;
    char *urlWithoutComProtocol = NULL;
    int length = 0;

    if ((length = strspn(url, "https://")) == strlen("https://") ||
        (length = strspn(url, "http://")) == strlen("http://")) {

        urlWithoutComProtocol = url + length;
        result = searchAfterComProtocol(urlWithoutComProtocol, fileName);
    }

    return result;
}

int getCountListMimeType() {

}

char **getListMimeTypeFileExt() {

}

char *getFileNameByUrl(char *url, char *mimeType) {

}