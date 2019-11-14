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
static void urlHelperSetRestFields(UrlHelper *pUrlHelper);
static void urlHelperSetFileNameAndExt(UrlHelper *pUrlHelper, const char *fileName, const char *fileExt);
static void expandAbsPath(UrlHelper *pUrlHelper, int newLength);
static void catUrlHelperFileNameAndFileExt(UrlHelper *pUrlHelper, ListFData *pList);

/**
 * Initialize the structure UrlHelper to get few parts of url
 * @param url : current url to view
 * @return OK pUrlHerper : pointer of structure UrlHelper,<br>
 * ERROR NULL
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
    if (pUrlHelper->result != UH_OK) {
        free(pUrlHelper);
        return NULL;
    }
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
        fprintf(stderr, "ERROR in fillUrlHelper : Problem with the domain name of url : %s\n", url);
        free(pUrlHelper->url);
        return;
    }

    urlHelperSetAbsPath(pUrlHelper);

    urlHelperSetRestFields(pUrlHelper);
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
 * Function to set absolute path of url in structure UrlHelper
 * @param pUrlHelper : pointer of structure UrlHelper
 */
static void urlHelperSetAbsPath(UrlHelper *pUrlHelper) {
    int length = 0;
    char *beginPath = NULL; // the absolute path of url begin to '/' of url after domain name
    char *absPathAndData = NULL; // the absolute path and additional data of url after '/'
    char *optionalData = NULL; // the parameters add with path of url after '?'

    if (pUrlHelper->isDomainName == 1) {
        length = getIndexAfterOccurStr(pUrlHelper->url, pUrlHelper->domainName);
        beginPath = pUrlHelper->url + length;

        if (strchr(beginPath, '/') != NULL && strlen(beginPath) > 1) {
            absPathAndData = strchr(beginPath, '/');
            optionalData = strchr(absPathAndData, '?');
            length = optionalData != NULL ? (int) (optionalData - absPathAndData) : (int) strlen(absPathAndData);

            pUrlHelper->absPath = strMallocCpy(absPathAndData, length);
            verifyPointer(pUrlHelper->absPath, "Problem to strMallocCpy absPath if UrlHelper\n");

            pUrlHelper->isAbsPath = 1;
        }
    }
}

/**
 * Function to set the rest of fields (file name and file extension) and adjust absolute path
 * @param pUrlHelper
 */
static void urlHelperSetRestFields(UrlHelper *pUrlHelper) {
    int lengthAbsPath = 0; // length of absolute path without file name
    char *fileName = NULL; // pointer of char correspond to file name of url without parameters
    char *fileExt = NULL; // pointer of char correspond to file extensions in file name of url

    if (pUrlHelper->isAbsPath == 1) {
        fileExt = strrchr(pUrlHelper->absPath, '.');

        if (fileExt != NULL && strlen(fileExt) > 1) {
            if (isFileExtExistsInList(fileExt)) { // function in fileExtTypeMime to check if fileExt exists in list
                fileName = strrchr(pUrlHelper->absPath, '/') + 1;

                urlHelperSetFileNameAndExt(pUrlHelper, fileName, fileExt); // set file name and file extension in UrlHelper

                lengthAbsPath = (int)(fileName - pUrlHelper->absPath);
                expandAbsPath(pUrlHelper, lengthAbsPath);
                return;
            }
        }

        lengthAbsPath = (int)strlen(pUrlHelper->absPath) + 1;
        expandAbsPath(pUrlHelper, lengthAbsPath);

        pUrlHelper->absPath[lengthAbsPath - 1] = '/';
    }
}

/**
 * Function to set file name and file extension in structure UrlHelper
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param fileName : file name to set in UrlHelper
 * @param fileExt : file extension to set in UrlHeler
 */
static void urlHelperSetFileNameAndExt(UrlHelper *pUrlHelper, const char *fileName, const char *fileExt) {

    pUrlHelper->fileName = strMallocCpy(fileName, (int) strlen(fileName));
    verifyPointer(pUrlHelper->fileName, "Problem strMallocCpy pUrlHelper->fileName in urlHelperSetFileName\n");
    pUrlHelper->isFileName = 1;

    pUrlHelper->fileExt = strMallocCpy(fileExt, (int) strlen(fileExt));
    verifyPointer(pUrlHelper->fileExt, "Problem strMallocCpy exitFile UrlHelper in urlHelperSetFileName\n");
    pUrlHelper->isFileExt = 1;
}

/**
 * Function to expand absolute path of UrlHelper to separate to other data after (filename or optional data)
 * @param pUrlHelper : pointer of structure UrlHelper
 * @param newLength : length to realloc absolute path
 */
static void expandAbsPath(UrlHelper *pUrlHelper, int newLength) {

    pUrlHelper->absPath = realloc(pUrlHelper->absPath, newLength + 1);
    verifyPointer(pUrlHelper->absPath, "Problem realloc pUrlHelper->absPath in expandAbsPath\n");
    pUrlHelper->absPath[newLength] = '\0';
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
    if (pUrlHelper->isAbsPath == 1) {
        pUrlHelper->isAbsPath = 1;
        free(pUrlHelper->absPath);
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