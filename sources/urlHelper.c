//
// Created by masat on 27/10/2019.
//

#include "urlHelper.h"

UrlHelper *initUrlHelper(const char *url) {
    UrlHelper *pUrlHelper = malloc(sizeof(UrlHelper));
    if (pUrlHelper == NULL) {
        //destroyApp();
        errorQuit("Problem malloc in initUrlHelper\n");
    }
    pUrlHelper->isDomainName = 0;
    pUrlHelper->isFileName = 0;
    pUrlHelper->isExtFile = 0;
    pUrlHelper->result = UH_OK;

    fillUrlHelper(pUrlHelper, url);

    return pUrlHelper;
}

static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url) {
    pUrlHelper->url = strMallocCpy(url, strlen(url));
    if (pUrlHelper->url == NULL) {
        //destroyApp();
        errorQuit("Problem malloc url in fillUrlHelper\n");
    }

    urlHelperSetDomainName(pUrlHelper);
    if (pUrlHelper->result == UH_NAME_PB) {
        //destroyApp();
        return;
    }
    urlHelperSetFileName(pUrlHelper);
}


void urlHelperSetDomainName(UrlHelper *pUrlHelper) {
    char *start = NULL;
    char *end = NULL;
    int length = 0;

    if ((length = getIndexAfterOccurStr(pUrlHelper->url, "https://")) > 0 ||
        (length = getIndexAfterOccurStr(pUrlHelper->url, "http://")) > 0) {
        start = pUrlHelper->url + length;
        if (start == NULL) {
            return;
        }
        end = strchr(start, '/');
        length = (end == NULL) ? strlen(start) : end - start;
        pUrlHelper->domainName = strMallocCpy(start, length);
        if (pUrlHelper->domainName == NULL) {
            //destroyApp()
            errorQuit("Problem strMallocCpy domainName in urlHelperSetDomainName\n");
        }
        if (strchr(pUrlHelper->domainName, '.') == NULL) {
            free(pUrlHelper->domainName);
            return;
        }
        pUrlHelper->isDomainName = 1;
    } else {
        pUrlHelper->result = UH_NAME_PB;
    }
}

void urlHelperSetFileName(UrlHelper *pUrlHelper) {

}


void destroyUrlHelper(UrlHelper *pUrlHelper) {
    if (pUrlHelper->isDomainName == 1) {
        pUrlHelper->isDomainName = 0;
        free(pUrlHelper->domainName);
    }
    if (pUrlHelper->isFileName == 1) {
        pUrlHelper->isFileName = 0;
        free(pUrlHelper->fileName);
    }
    if (pUrlHelper->isExtFile == 1) {
        pUrlHelper->isExtFile = 0;
        free(pUrlHelper->extFile);
    }

    free(pUrlHelper);
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
//    UHRes result = UH_WITHOUT_FILE_EXT;
////    int length = 0;
////    char *urlResource = NULL;
////    char *checkPoint = NULL;
////
////    if (urlWithoutComProtocol != NULL) {
////        urlResource = strrchr(urlWithoutComProtocol, '/');
////        if (urlResource != NULL) {
////            length = strrchr(urlResource, '?') != NULL ? strrchr(urlResource, '?') - urlResource + 1 : strlen(urlResource) + 1;
////            urlResource = getFileName(urlResource, length);
////            checkPoint = strrchr(urlResource, '.');
////            if (checkPoint != NULL) {
////                result = UH_WITH_FILE_EXT;
////            }
////            if (fileName != NULL) {
////                *fileName = urlResource;
////                if (*fileName == NULL) {
////                    result = UH_MEM_PB;
////                }
////            } else {
////                free(urlResource);
////            }
////        }
////    }
////
////    return result;
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
