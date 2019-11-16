//
// Created by masat on 12/11/2019.
//

#include "../headers/urlSearcher.h"

static void getArrStrOfUrls(String *pString, const char *urlNoRes, const char *page, const char *contentType);

static void getUrlInHtmlPage(String *pString, const char *currentPosPage, int *position);

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
char **getAllUrlsInPage(const char *url, const char *contentType, const char *page, int *count) {
    char **arrStr = NULL;
    char *urlWithPath = NULL;
    UrlHelper *pUrlHelper = NULL;
    String *listChar = NULL;

    pUrlHelper = initUrlHelper(url);
    if (pUrlHelper->result == UH_NAME_PB) {
        free(pUrlHelper);
        return NULL;
    }

    listChar = initString(500, 1.5);
    if (listChar == NULL) {
        destroyUrlHelper(pUrlHelper);
        return NULL;
    }

    urlWithPath = getUrlWithAbsPath(pUrlHelper);

    getArrStrOfUrls(listChar, urlWithPath, page, contentType);

    arrStr = NULL;//destroyListStrAndReturnArrStr(listStr, count);

    return arrStr;
}

static void getArrStrOfUrls(String *pString, const char *urlNoRes, const char *page, const char *contentType) {
    int position = 0;
    int length = (int) strlen(page);

    // TODO : change the start search to "src=" or "href="
    // TODO : get if after they have " or ' or alphabet
    // TODO : change after if it contain https or http
    // TODO : if https or http get url
    // TODO : else if it "//" after so add before the protocol of com of url
    // TODO : if its "/" add the url with absolute path
    if (strcmp(contentType, "text/html") == 0) {
        while (position < length) {
            getUrlInHtmlPage(pString, page + position, &position);
        }
    } else {
        while (position < length) {
            getUrlInPage(pString, page + position, &position);
        }
    }
}

static void getUrlInHtmlPage(String *pString, const char *currentPosPage, int *position) {

}

static void getUrlInPage(String *pString, const char *currentPosPage, int *position) {
    char *checkUrl = NULL;
    char *startUrl = NULL;
    char *endUrl = NULL;
    char container = 0;
    int lengthUrl = 0;

    if ((checkUrl = strstr(currentPosPage, "https:")) || (checkUrl = strstr(currentPosPage, "http:"))) {
//        if (checkUrl[-1] != '=') {
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