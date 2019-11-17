/*
 *  Filename    : urlSearcher.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Get the HTTP and HTTPS urls in one page html
 */

#include "../headers/urlSearcher.h"

static void initFieldUrlSearcher(UrlSearcher *pUrlSearcher);
static void setFieldsUrlSearcher(UrlSearcher *pUrlSearcher, UrlHelper *pUrlHelper, const char *url);
static void setContentPage(UrlSearcher *pUrlSearch, const char *filePath);
static char *getProtocolCom(const char *url);

static void getArrStrOfUrls(String *pString, UrlSearcher *pUrlSearch, const char *contentType);
static void saveUrlsInFile(const char *contentUrls, const char *dirPath);
static void getUrlInHtmlPage(String *pString, UrlSearcher *pUrlSearch, const char *ptStartOccur);
static char *getUrlToAdd(UrlSearcher *pUrlSearch, int *lengthUrl);
static char *addProtocolComAndUrl(UrlSearcher *pUrlSearch, int lengthUrl);
static char *addHttpUrl(UrlSearcher *pUrlSearcher, int lengthUrl);
static char *addRootPathAndUrl(UrlSearcher *pUrlSearch, int lengthUrl);


/**
 * Function to get all http url in page that each url is unique
 * @param UrlNoRes : the url with only http syntax and domain name like "https://www.google.com"
 * @param page : the page that correspond to the
 * @param count : number of url
 * @return OK allUrls : array of url that fetch in page, <br>
 * ERROR NULL
 */
char **getAllUrlsInPage(const char *url, const char *contentType, const char *filePath, int *count, const char *dirPath) {
    UrlSearcher *pUrlSearcher = NULL;
    char **arrStr = NULL;
    String *pString = initString(500, 1.5);
    if (pString == NULL) {
        return NULL;
    }
    pUrlSearcher = initUrlSearcher(url, filePath);
    if (pUrlSearcher == NULL) {
        free(pString);
        return NULL;
    }

    getArrStrOfUrls(pString, pUrlSearcher, contentType);

    saveUrlsInFile(pString->content, dirPath);
    arrStr = properStrSplit(pString->content, "\n", count);

    destroyString(pString);
    destroyUrlSearcher(pUrlSearcher);

    return arrStr;
}

static void saveUrlsInFile(const char *contentUrls, const char *dirPath) {
    FILE *fp = NULL;
    char *fileUrlsName = strMallocCat(dirPath, "/all_urls_names.txt");
    verifyPointer(fileUrlsName, "Problem strMallocCat in saveUrlsInFile\n");

    if (contentUrls != NULL && strlen(contentUrls) > 1) {
        mkdirP(dirPath);

        fp = fopen(fileUrlsName, "ab");
        verifyPointer(fp, "Problem open file in saveUrlsInFile\n");

        fprintf(fp, "%s", contentUrls);

        fclose(fp);
    }

    free(fileUrlsName);
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
        pUrlSearch->currentPage = pUrlSearch->page;
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
            urlToAdd = getUrlToAdd(pUrlSearch, &lengthUrl);
        }
        if (urlToAdd != NULL && strstr(pString->content, urlToAdd) == NULL) {
            addString(pString, urlToAdd);
            free(urlToAdd);
        }
        if (lengthUrl == 0) {
            pUrlSearch->position += (int)strlen(ptStartOccur) + startIndex;
        } else {
            pUrlSearch->position += lengthUrl + startIndex + 2;
        }
    } else {
        pUrlSearch->position += ((int)strlen(pUrlSearch->currentPage));
    }
    pUrlSearch->currentPage = pUrlSearch->page + pUrlSearch->position;
}

static char *getUrlToAdd(UrlSearcher *pUrlSearch, int *lengthUrl) {
    char *urlToAdd = NULL;

    pUrlSearch->end = strchr(pUrlSearch->start, pUrlSearch->container);
    *lengthUrl = (int) (pUrlSearch->end - pUrlSearch->start);

    if (strncmp("//", pUrlSearch->start, 2) == 0) {
        urlToAdd = addProtocolComAndUrl(pUrlSearch, *lengthUrl);

    } else if (strncmp("https://", pUrlSearch->start, (int) strlen("https://")) == 0 ||
               strncmp("http://", pUrlSearch->start, (int) strlen("http://")) == 0) {
        urlToAdd = addHttpUrl(pUrlSearch, *lengthUrl);

    } else {
        urlToAdd = addRootPathAndUrl(pUrlSearch, *lengthUrl);
    }

    return urlToAdd;
}

static char *addProtocolComAndUrl(UrlSearcher *pUrlSearch, int lengthUrl) {
    char *urlToAdd = NULL;
    char *withoutProtocolCom = strMallocCpy(pUrlSearch->start, lengthUrl + 1);
    if (withoutProtocolCom == NULL) {
        return NULL;
    }

    withoutProtocolCom[lengthUrl] = '\n';
    if (pUrlSearch->isProtocolCom == 1) {
        urlToAdd = strMallocCat(pUrlSearch->protocolCom, withoutProtocolCom);
        if (urlToAdd == NULL) {
            free(withoutProtocolCom);
            return NULL;
        }
    } else {
        free(withoutProtocolCom);
    }

    return urlToAdd;
}

static char *addHttpUrl(UrlSearcher *pUrlSearch, int lengthUrl) {
    char *urlToAdd = NULL;

    urlToAdd = strMallocCpy(pUrlSearch->start, lengthUrl + 1);
    verifyPointer(urlToAdd, "Problem strMallocCpy urlToAdd in addHttpUrl in urlSearcher.c\n");

    urlToAdd[lengthUrl] = '\n';

    return urlToAdd;
}

static char *addRootPathAndUrl(UrlSearcher *pUrlSearch, int lengthUrl) {
    char *urlToAdd = NULL;
    char *withoutNameDomain = NULL;

    if (pUrlSearch->start[0] == '/') {
        withoutNameDomain = strMallocCpy(pUrlSearch->start + 1, lengthUrl);
        withoutNameDomain[lengthUrl - 1] = '\n';
    } else {
        withoutNameDomain = strMallocCpy(pUrlSearch->start, lengthUrl + 1);
        withoutNameDomain[lengthUrl] = '\n';
        if (strchr(withoutNameDomain, ':') != NULL) {
            free(withoutNameDomain);
            return NULL;
        }
    }
    if (pUrlSearch->isRootPath == 1) {
        urlToAdd = strMallocCat(pUrlSearch->rootPath, withoutNameDomain);
        if (urlToAdd == NULL) {
            free(withoutNameDomain);
            return NULL;
        }
    } else {
        free(withoutNameDomain);
    }

    return urlToAdd;
}

void destroyUrlSearcher(UrlSearcher *pUrlSearcher) {
    if (pUrlSearcher->isProtocolCom == 1) {
        free(pUrlSearcher->protocolCom);
    }
    if (pUrlSearcher->isRootPath == 1) {
        free(pUrlSearcher->rootPath);
    }
    if (pUrlSearcher->isPointOccur == 1) {
        free(pUrlSearcher->pointOccur);
    }
    if (pUrlSearcher->isPage == 1) {
        free(pUrlSearcher->page);
    }

    free(pUrlSearcher);
}