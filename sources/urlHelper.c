//
// Created by masat on 27/10/2019.
//

#include "urlHelper.h"

/**
 * Set the file name in UrlHelper
 * @param pUrlHelper
 */
static void urlHelperSetFileName(UrlHelper *pUrlHelper) {
    int length = 0;
    char *absPath =  NULL; // the absolute path of url begin to '/' of url after domain name
    char *fileName = NULL; // the file name of url after the last '/' of url without parameters
    char *optionalData = NULL; // the parameters add with path of url after '?'

    if (pUrlHelper->isDomainName == 1) {
        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
        absPath = pUrlHelper->url + length;

        if (strrchr(absPath, '/') != NULL && strlen(absPath) > 1) {
            fileName = strrchr(absPath, '/') + 1;
            optionalData = strchr(fileName, '?');
            length = optionalData != NULL ? (int)(optionalData - fileName) : (int)strlen(fileName);

            pUrlHelper->fileName = strMallocCpy(fileName, length);
            if (pUrlHelper->fileName == NULL) {
                destroyApp();
                errorQuit("Problem to strMallocCpy fileName if UrlHelper\n");
            }
            pUrlHelper->isFileName = 1;
        }
    }
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
        length = (end == NULL) ? (int)strlen(start) : (int)(end - start);
        pUrlHelper->domainName = strMallocCpy(start, length);
        if (pUrlHelper->domainName == NULL) {
            destroyApp();
            errorQuit("Problem strMallocCpy domainName in urlHelperSetDomainName\n");
        }
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
 * Function to set ext file of file name in url
 * @param pHelper
 */
static void urlHelperSetExtFile(UrlHelper *pUrlHelper) {
    char *extFile = NULL; // extension file in file name of url

    if (pUrlHelper->isFileName == 1) {
        extFile = strrchr(pUrlHelper->fileName, '.');
        if (extFile != NULL && strlen(extFile) > 1) {
            pUrlHelper->extFile = strMallocCpy(extFile + 1, (int)strlen(extFile));
            if (pUrlHelper->extFile == NULL) {
                destroyApp();
                errorQuit("Problem strMallocCpy exitFile UrlHelper\n");
            }
            pUrlHelper->isExtFile = 1;
        }
    }
}

/**
 * Fill the fields of UrlHelper
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param url : the current url
 */
static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url) {
    pUrlHelper->url = strMallocCpy(url, (int)strlen(url));
    if (pUrlHelper->url == NULL) {
        destroyApp();
        errorQuit("Problem malloc url in fillUrlHelper\n");
    }

    urlHelperSetDomainName(pUrlHelper);
    if (pUrlHelper->result == UH_NAME_PB) {
        return;
    }
    urlHelperSetFileName(pUrlHelper);
    urlHelperSetExtFile(pUrlHelper);
}

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return : pointer of structure UrlHelper
 */
UrlHelper *initUrlHelper(const char *url) {
    UrlHelper *pUrlHelper = malloc(sizeof(UrlHelper));
    if (pUrlHelper == NULL) {
        destroyApp();
        errorQuit("Problem malloc in initUrlHelper\n");
    } else {
        pUrlHelper->domainName = NULL;
        pUrlHelper->fileName = NULL;
        pUrlHelper->extFile = NULL;

        pUrlHelper->isDomainName = 0;
        pUrlHelper->isFileName = 0;
        pUrlHelper->isExtFile = 0;
        pUrlHelper->result = UH_OK;

        fillUrlHelper(pUrlHelper, url);
    }

    return pUrlHelper;
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

/**
 * Get the file extension depends to mime type
 * @param pUrlHelper
 * @return
 * 1 : Success to set extention file in structure UrlHelper
 * 0 : not set because of not found extention file depend to mime type
 */
int getExtFileByMimeType(UrlHelper *pUrlHelper) {
    // TODO : get the ext file by mime type when the file extension is not in url
    fprintf(stderr, "The function to get file extention by mime type is not implemented, maybe soon\n");

    return 0;
}