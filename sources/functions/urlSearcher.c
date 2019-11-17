//
// Created by masat on 12/11/2019.
//

#include "../headers/urlSearcher.h"
static void initFieldUrlSearcher(UrlSearcher *pUrlSearcher);
static void setFieldsUrlSearcher(UrlSearcher *pUrlSearcher, UrlHelper *pUrlHelper, const char *url);
static void setContentPage(UrlSearcher *pUrlSearch, const char *filePath);
static char *getProtocolCom(const char *url);

static void getArrStrOfUrls(String *pString, UrlSearcher *pUrlSearch, const char *contentType);
static void getUrlInHtmlPage(String *pString, UrlSearcher *pUrlSearch, const char *ptStartOccur);
static char *getUrlToAdd(UrlSearcher *pUrlSearch);
static char *addProtocolComAndUrl(UrlSearcher *pUrlSearch, int lengthUrl);
static char *addRootPathAndUrl(UrlSearcher *pUrlSearch, int lengthUrl);
static void getUrlInPage(String *pString, const char *page, int *position);
static void addUrlInList(String *pString, const char *startUrl, int lengthUrl);

/**
 * Function to get all http url in page that each url is unique
 * @param UrlNoRes : the url with only http syntax and domain name like "https://www.google.com"
 * @param page : the page that correspond to the
 * @param count : number of url
 * @return OK allUrls : array of url that fetch in page, <br>
 * ERROR NULL
 */
char **getAllUrlsInPage(const char *url, const char *contentType, const char *filePath, int *count) {
    UrlSearcher *pUrlSearcher = initUrlSearcher(url,filePath);
    char **arrStr = NULL;
    String *pString = initString(500, 1.5);
    if (pString == NULL) {
        return NULL;
    }

    getArrStrOfUrls(pString, pUrlSearcher, contentType);

    arrStr = properStrSplit(pString->content, "\n", count);

    destroyString(pString);
    destroyUrlSearcher(pUrlSearcher);

    return arrStr;
}

UrlSearcher *initUrlSearcher(const char *url, const char *filePath) {
    UrlHelper *pUrlHelper = NULL;
    UrlSearcher *pUrlSearcher = malloc(sizeof(UrlSearcher));
    if (pUrlSearcher == NULL) {
        fprintf(stderr, "Problem malloc UrlSearcher\n");
        return NULL;
    }
    pUrlHelper = initUrlHelper(url);
    if (pUrlHelper->result == UH_NAME_PB) {
        free(pUrlSearcher);
        free(pUrlHelper);
        return NULL;
    }
    initFieldUrlSearcher(pUrlSearcher);

    setFieldsUrlSearcher(pUrlSearcher, pUrlHelper, url);
    setContentPage(pUrlSearcher, filePath);

    return pUrlSearcher;
}

static void initFieldUrlSearcher(UrlSearcher *pUrlSearcher) {
    pUrlSearcher->protocolCom = NULL;
    pUrlSearcher->rootPath = NULL;
    pUrlSearcher->currentPage = NULL;
    pUrlSearcher->pointOccur = NULL;
    pUrlSearcher->page = NULL;

    pUrlSearcher->container = 0;

    pUrlSearcher->isPointOccur = 0;
    pUrlSearcher->isRootPath = 0;
    pUrlSearcher->isProtocolCom = 0;
    pUrlSearcher->isPage = 0;
    pUrlSearcher->position = 0;
}

static void setFieldsUrlSearcher(UrlSearcher *pUrlSearcher, UrlHelper *pUrlHelper, const char *url) {
    pUrlSearcher->protocolCom = getProtocolCom(url);
    verifyPointer(pUrlSearcher->protocolCom, "Problem to get protocol com in initUrlSearcher\n");
    pUrlSearcher->isProtocolCom = 1;

    pUrlSearcher->rootPath = getUrlWithRootPath(pUrlHelper);
    verifyPointer(pUrlSearcher->rootPath, "Problem getUrlWithRootPath in initUrlSearcher\n");
    pUrlSearcher->isRootPath = 1;
}

static void setContentPage(UrlSearcher *pUrlSearch, const char *filePath) {
    pUrlSearch->page = getContentInFile(filePath, "rb");
    verifyPointer(pUrlSearch->page, "Problem to get content file in setContentPage or UrlSearcher\n");

    pUrlSearch->isPage = 1;

}

static char *getProtocolCom(const char *url) {
    char *protocolCom = NULL;
    int indexEndProtocolCom = 0;

    if ((indexEndProtocolCom = getIndexAfterOccurStr(url, "http:")) ||
        (indexEndProtocolCom = getIndexAfterOccurStr(url, "https:"))) {
        protocolCom = strMallocCpy(url, indexEndProtocolCom);
    }

    return protocolCom;
}

/// START GET ALL URL ///

static void getArrStrOfUrls(String *pString, UrlSearcher *pUrlSearch, const char *contentType) {
    int length = (int) strlen(pUrlSearch->page);
    pUrlSearch->currentPage = pUrlSearch->page;

    if (strcmp(contentType, "text/html") == 0) {
        while (pUrlSearch->position < length) {
            getUrlInHtmlPage(pString, pUrlSearch, "src=");
        }
        pUrlSearch->position = 0;
        while (pUrlSearch->position < length) {
            getUrlInHtmlPage(pString, pUrlSearch, "href=");
        }
    }
}

static void getUrlInHtmlPage(String *pString, UrlSearcher *pUrlSearch, const char *ptStartOccur) {
    int startIndex = getIndexAfterOccurStr(pUrlSearch->currentPage, ptStartOccur);
    char *urlToAdd = NULL;
    int lengthUrl = 0;

    if (startIndex > 0) {
        if (pUrlSearch->currentPage[startIndex] == '"' || pUrlSearch->currentPage[startIndex] == '\'') {
            pUrlSearch->container = pUrlSearch->currentPage[startIndex];
            pUrlSearch->start = &pUrlSearch->currentPage[startIndex] + 1;
            urlToAdd = getUrlToAdd(pUrlSearch);
        }
        if (urlToAdd != NULL) {
            addString(pString, urlToAdd);
            free(urlToAdd);
        }
        pUrlSearch->position += lengthUrl + (int) (pUrlSearch->start - pUrlSearch->currentPage);
    } else {
        pUrlSearch->position += (int) strlen(pUrlSearch->currentPage);
    }
    pUrlSearch->currentPage = pUrlSearch->page + pUrlSearch->position;
}

static char *getUrlToAdd(UrlSearcher *pUrlSearch) {
    int lengthUrl = 0;
    char *urlToAdd = NULL;

    pUrlSearch->end = strchr(pUrlSearch->start, pUrlSearch->container);
    lengthUrl = (int) (pUrlSearch->end - pUrlSearch->start);
    if (strncmp("//", pUrlSearch->start, 2) == 0) {
        urlToAdd = addProtocolComAndUrl(pUrlSearch, lengthUrl);
    } else if (pUrlSearch->start[0] == '/') {
        urlToAdd = addRootPathAndUrl(pUrlSearch, lengthUrl);
    } else {
        urlToAdd = strMallocCpy(pUrlSearch->start , lengthUrl + 1);
        urlToAdd[lengthUrl] = '\n';
    }

    return urlToAdd;
}

static char *addProtocolComAndUrl(UrlSearcher *pUrlSearch, int lengthUrl) {
    // replace // to protocol com https:// or http://

    return NULL;
}

static char *addRootPathAndUrl(UrlSearcher *pUrlSearch, int lengthUrl) {
    return NULL;
}

static void getUrlInPage(String *pString, const char *currentPosPage, int *position) {
    char *checkUrl = NULL;
    char *startUrl = NULL;
    char *endUrl = NULL;
    char container = 0;
    int lengthUrl = 0;

    if ((checkUrl = strstr(currentPosPage, "https:")) || (checkUrl = strstr(currentPosPage, "http:"))) {
//        if (checkUrl[-1] == '"' || checkUrl[-1] == '\'') {
//            container = checkUrl[-1];
//            startUrl = checkUrl;
//            if (container > 0) {
//                endUrl = strchr(checkUrl, container);
//                if (endUrl == NULL) {
//                    fprintf(stderr, "Problem url\n");
//                    return;
//                }
//            }
//            lengthUrl = (int)(endUrl - startUrl);
//            addUrlInList(pString, startUrl, lengthUrl);
//            *position += lengthUrl + (int)(startUrl - currentPosPage);
//        }
    } else {
        *position += (int) strlen(currentPosPage);
    }
}

static void addUrlInList(String *pString, const char *startUrl, int lengthUrl) {
    char *url = NULL;

    url = strMallocCpy(startUrl, lengthUrl + 1);
    verifyPointer(url, "Problem to strMalloc url in function addUrlInListAndUpdatePosition\n");
    strcat(url, "\n");
    addString(pString, url);
    free(url);
}

void destroyUrlSearcher(UrlSearcher *pUrlSearcher) {
    if (pUrlSearcher->isProtocolCom != 1) {
        free(pUrlSearcher->protocolCom);
    }
    if (pUrlSearcher->isRootPath != 1) {
        free(pUrlSearcher->rootPath);
    }
    if (pUrlSearcher->isProtocolCom != 1) {
        free(pUrlSearcher->page);
    }
    if (pUrlSearcher->isPointOccur != 1) {
        free(pUrlSearcher->pointOccur);
    }

    free(pUrlSearcher);
}