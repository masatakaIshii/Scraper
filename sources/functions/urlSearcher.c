//
// Created by masat on 12/11/2019.
//

#include "../headers/urlSearcher.h"
static void getArrStrOfUrls(ListStr *listStr, const char *urlNoRes, const char *page);

/**
 * Function to get all http url in page that each url is unique
 * @param UrlNoRes : the url with only http syntax and domain name like "https://www.google.com"
 * @param page : the page that correspond to the
 * @param count : number of url
 * @return allUrls : array of url that fetch in page
 */
char **getAllUrlsInPage(const char *urlNoRes, const char *contentType, const char *page, int *count) {
    char **arrStr = NULL;
    ListStr *listStr = initListStr(10);
    if (listStr == NULL) {
        return NULL;
    }

    getArrStrOfUrls(listStr, urlNoRes, page);

    return arrStr;
}

static void getArrStrOfUrls(ListStr *listStr, const char *urlNoRes, const char *page) {
    // TODO to begin to search url and add in list
}