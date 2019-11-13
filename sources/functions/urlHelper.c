/*
 *  Filename    : urlHelper.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to decompose and manage parts of URL
 */
#include "../headers/urlHelper.h"

static void fillUrlHelper(UrlHelper *pUrlHelper, const char *url);
static void urlHelperSetDomainName(UrlHelper *pUrlHelper);
static void urlHelperSetAbsPath(UrlHelper *pUrlHelper);
static void urlHelperSetFileName(UrlHelper *pUrlHelper);
static void urlHelperSetExtFile(UrlHelper *pUrlHelper);

static void catUrlHelperFileNameAndFileExt(UrlHelper *pUrlHelper, ListFData *pList);

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return : pointer of structure UrlHelper
 */
UrlHelper *initUrlHelper(const char *url) {
    UrlHelper *pUrlHelper = malloc(sizeof(UrlHelper));
    verifyPointer(pUrlHelper, "Problem malloc in initUrlHelper\n");

    pUrlHelper->domainName = NULL;
    pUrlHelper->absPath = NULL;
    pUrlHelper->fileName = NULL;
    pUrlHelper->fileExt = NULL;

    pUrlHelper->isDomainName = 0;
    pUrlHelper->isAbsPath = 0;
    pUrlHelper->isFileName = 0;
    pUrlHelper->isFileExt = 0;
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
    urlHelperSetAbsPath(pUrlHelper);
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

static void urlHelperSetAbsPath(UrlHelper *pUrlHelper) {
    int length = 0;
    char *beginPath = NULL; // the absolute path of url begin to '/' of url after domain name
    char *absPathAndData = NULL; // the absolute path and additional data of url after '/'
    char *absPath = NULL; // the only absolute path
    char *optionalData = NULL; // the parameters add with path of url after '?'

    if (pUrlHelper->isDomainName == 1) {
        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
        beginPath = pUrlHelper->url + length;

        if (strchr(beginPath, '/') != NULL && strlen(beginPath) > 1) {
            absPathAndData = strchr(beginPath, '/');
            optionalData = strchr(absPathAndData, '?');
            length = optionalData != NULL ? (int) (optionalData - absPathAndData) : (int) strlen(absPathAndData);

            pUrlHelper->absPath = checkIfThereAreFileName(absPathAndData, length);
            verifyPointer(pUrlHelper->absPath, "Problem to strMallocCpy absPath if UrlHelper\n");

            pUrlHelper->isAbsPath = 1;
        }
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
//
//    if (pUrlHelper->isDomainName == 1) {
//        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
//        absPath = pUrlHelper->url + length;
//
//        if (strrchr(absPath, '/') != NULL && strlen(absPath) > 1) {
//            fileName = strrchr(absPath, '/') + 1;
//            optionalData = strchr(fileName, '?');
//            length = optionalData != NULL ? (int) (optionalData - fileName) : (int) strlen(fileName);
//
//            pUrlHelper->fileName = strMallocCpy(fileName, length);
//            verifyPointer(pUrlHelper->fileName, "Problem to strMallocCpy fileName if UrlHelper\n");
//
//            pUrlHelper->isFileName = 1;
//        }
//    }
}

/**
 * Function to set ext file of file name in url
 * @param pHelper
 */
static void urlHelperSetExtFile(UrlHelper *pUrlHelper) {
    char *fileExt = NULL; // file extensions in file name of url

    if (pUrlHelper->isFileName == 1) {
        fileExt = strrchr(pUrlHelper->fileName, '.');
        if (fileExt != NULL && strlen(fileExt) > 1) {
            if (isFileExtExistsInList(fileExt)) { // function in fileExtTypeMime to check if fileExt exists in list
                pUrlHelper->fileExt = strMallocCpy(fileExt, (int) strlen(fileExt));
                verifyPointer(pUrlHelper->fileExt, "Problem strMallocCpy exitFile UrlHelper\n");

                pUrlHelper->isFileExt = 1;
            }
        }
    }
}

/**
 * Function to set file name when there are not indicated in URL
 * @param pUrlHelper
 * @param fileNameNoExt
 * @param mimeType
 * @return OK 1, ERROR 0, WARNING 2
 */
int setFileNameWhenNoOneInUrl(UrlHelper *pUrlHelper, const char *fileNameNoExt, char *mimeType) {
    if (pUrlHelper->isFileName > 0) {
        fprintf(stderr, "WARNING : the file name in already implemented, fileName : %s\n", pUrlHelper->fileName);
        return 2;
    }

    pUrlHelper->fileName = strMallocCpy(fileNameNoExt, (int)strlen(fileNameNoExt));
    verifyPointer(pUrlHelper->fileName, "Problem strMallocCpy pUrlHelper->fileName in function setFileNameWhenNoOneInUrl\n");
    pUrlHelper->isFileName = 1;

    return setFileExtInFileName(pUrlHelper, mimeType);
}

/**
 * Function to set file extension in file name
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param mimeType : the mime type to get file extension
 * @return OK 1, ERROR 0, WARNING 2
 */
int setFileExtInFileName(UrlHelper *pUrlHelper, char *mimeType) {
    ListFData *pList = NULL;

    if (pUrlHelper->isFileName == 0) {
        fprintf(stderr, "ERROR : In function setFileExtInFileName, no file name, not possible de set file extension for URL : %s\n", pUrlHelper->url);
        return 0;
    }

    if (pUrlHelper->isFileExt == 0) {
        pList = fillListFData(mimeType, FILE_EXT);
        if (pList != NULL && pList->numberData > 0) {
            catUrlHelperFileNameAndFileExt(pUrlHelper, pList);
        } else {
            fprintf(stderr, "\nWARNING : Mime %s is not in list\n", mimeType);
            return 2;
        }
    }

    return 1;
}

/**
 * Concat file name of UrlHelper and file extensions
 * @param pUrlHelper
 * @param pList
 */
static void catUrlHelperFileNameAndFileExt(UrlHelper *pUrlHelper, ListFData *pList) {
    char *temp = NULL;
    int index = 0;

    index = (pList->numberData > 1) ? 1 : 0;

    pUrlHelper->fileExt = strMallocCpy(pList->data[index], (int)strlen(pList->data[index]));
    verifyPointer(pUrlHelper->fileExt, "Problem strMallocCpy fileExt");
    pUrlHelper->isFileExt = 1;

    temp = pUrlHelper->fileName;
    pUrlHelper->fileName = strMallocCat(temp, pUrlHelper->fileExt);

    free(temp);
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
    if (pUrlHelper->isFileExt == 1) {
        pUrlHelper->isFileExt = 0;
        free(pUrlHelper->fileExt);
    }

    free(pUrlHelper);
}