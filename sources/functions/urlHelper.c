//
// Created by masat on 27/10/2019.
//

#include "../headers/urlHelper.h"

static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url);
static void urlHelperSetDomainName(UrlHelper *pUrlHelper);
static void urlHelperSetFileName(UrlHelper *pUrlHelper);
static void urlHelperSetExtFile(UrlHelper *pUrlHelper);

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return : pointer of structure UrlHelper
 */
UrlHelper *initUrlHelper(const char *url) {
    UrlHelper *pUrlHelper = malloc(sizeof(UrlHelper));
    verifyPointer(pUrlHelper, "Problem malloc in initUrlHelper\n");

    pUrlHelper->domainName = NULL;
    pUrlHelper->fileName = NULL;
    pUrlHelper->extFile = NULL;

    pUrlHelper->isDomainName = 0;
    pUrlHelper->isFileName = 0;
    pUrlHelper->isExtFile = 0;
    pUrlHelper->result = UH_OK;

    fillUrlHelper(pUrlHelper, url);

    return pUrlHelper;
}

/**
 * Fill the fields of UrlHelper
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param url : the current url
 */
static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url) {
    pUrlHelper->url = strMallocCpy(url, (int) strlen(url));
    verifyPointer(pUrlHelper->url, "Problem malloc url in fillUrlHelper\n");

    urlHelperSetDomainName(pUrlHelper);
    if (pUrlHelper->result == UH_NAME_PB) {
        return;
    }
    urlHelperSetFileName(pUrlHelper);
    urlHelperSetExtFile(pUrlHelper);
}

/**
 * Set the domain name in structure UrlHelper
 * @param pUrlHelper
 */
static void urlHelperSetDomainName(UrlHelper *pUrlHelper) {
    char *start = NULL; // start of domain name in url
    char *end = NULL; // end of domain name in url
    int length = 0;

    if ((length = getIndexAfterOccurStr(pUrlHelper->url, "https://")) > 0 ||
        (length = getIndexAfterOccurStr(pUrlHelper->url, "http://")) > 0) {
        start = pUrlHelper->url + length;
        if (start == NULL) {
            return;
        }
        end = strchr(start, '/');
        length = (end == NULL) ? (int) strlen(start) : (int) (end - start);
        pUrlHelper->domainName = strMallocCpy(start, length);
        verifyPointer(pUrlHelper->domainName, "Problem strMallocCpy domainName in urlHelperSetDomainName\n");

        if (strchr(pUrlHelper->domainName, '.') == NULL) {
            free(pUrlHelper->domainName);
            pUrlHelper->result = UH_NAME_PB;
            return;
        }
        pUrlHelper->isDomainName = 1;
    } else {
        pUrlHelper->result = UH_NAME_PB;
    }
}

/**
 * Set the file name in UrlHelper
 * @param pUrlHelper
 */
static void urlHelperSetFileName(UrlHelper *pUrlHelper) {
    int length = 0;
    char *absPath = NULL; // the absolute path of url begin to '/' of url after domain name
    char *fileName = NULL; // the file name of url after the last '/' of url without parameters
    char *optionalData = NULL; // the parameters add with path of url after '?'

    if (pUrlHelper->isDomainName == 1) {
        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
        absPath = pUrlHelper->url + length;

        if (strrchr(absPath, '/') != NULL && strlen(absPath) > 1) {
            fileName = strrchr(absPath, '/') + 1;
            optionalData = strchr(fileName, '?');
            length = optionalData != NULL ? (int) (optionalData - fileName) : (int) strlen(fileName);

            pUrlHelper->fileName = strMallocCpy(fileName, length);
            verifyPointer(pUrlHelper->fileName, "Problem to strMallocCpy fileName if UrlHelper\n");

            pUrlHelper->isFileName = 1;
        }
    }
}

/**
 * Function to set ext file of file name in url
 * @param pHelper
 */
static void urlHelperSetExtFile(UrlHelper *pUrlHelper) {
    char *extFile = NULL; // extension file in file name of url

    if (pUrlHelper->isFileName == 1) {
        extFile = strrchr(pUrlHelper->fileName, '.');
        if (extFile != NULL && strlen(extFile) > 1) {
            if (isFileExtExistsInList(extFile)) {
                pUrlHelper->extFile = strMallocCpy(extFile, (int) strlen(extFile));
                verifyPointer(pUrlHelper->extFile, "Problem strMallocCpy exitFile UrlHelper\n");

                pUrlHelper->isExtFile = 1;
            }
        }
    }
}

int setExtFileInFileName(UrlHelper *pUrlHelper, char *mimeType) {

    //printf("%s", listMimeTypeExtFile);
    // TODO : add test in urlHelper and manage set ext file depend to mimeType
    return 0;
}

/**
 * Destroy the pointer of structure UrlHelper
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