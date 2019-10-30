//
// Created by masat on 27/10/2019.
//

#include "urlHelper.h"

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return : pointer of structure UrlHelper
 */
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

/**
 * fill the fields of UrlHelper
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param url : the current url
 */
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

/**
 * set the domain name in structure UrlHelper
 * @param pUrlHelper
 */
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

/**
 * set the file name in UrlHelper
 * @param pUrlHelper
 */
void urlHelperSetFileName(UrlHelper *pUrlHelper) {
    int length = 0;
    char *absPath =  NULL;
    char *fileName = NULL;
    char *optionalData = NULL;

    if (pUrlHelper->isDomainName == 1) {
        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
        absPath = pUrlHelper->url + length;

        if (strrchr(absPath, '/') != NULL && strlen(absPath) > 1) {
            fileName = strrchr(absPath, '/') + 1;
            optionalData = strchr(fileName, '?');
            length = optionalData != NULL ? optionalData - fileName : strlen(fileName);

            pUrlHelper->fileName = strMallocCpy(fileName, length);
            pUrlHelper->isFileName = 1;
        }
    }
}

/**
 * destroy the pointer of structure UrlHelper
 * @param pUrlHelper
 */
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