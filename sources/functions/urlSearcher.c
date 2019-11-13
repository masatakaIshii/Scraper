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

    arrStr = destroyListStrAndReturnArrStr(listStr, count);

    return arrStr;
}

static void getArrStrOfUrls(ListStr *listStr, const char *urlNoRes, const char *page) {
    char *url = NULL;
    char *checkUrl = strstr(page, "https");
    char *startUrl = NULL;
    char *endUrl = NULL;
    char container = 0;
    

    if (checkUrl != NULL) {
        if (checkUrl[-1] != '=') {
            container = checkUrl[-1];
            startUrl = checkUrl;
            if (container > 0) {
                checkUrl = strchr(checkUrl, container);
                if (checkUrl == NULL) {
                    fprintf(stderr, "Problem url\n");
                    return;
                }
                url = strMallocCpy(startUrl, checkUrl - startUrl);
                listStrAdd(listStr, url);
            }
        }
    } else {
        printf("Bizzare\n");
    }
    // -faire une boucle jusqu'à qu'il n'y ait pas http ou https
    // -check s'il n'y a pas de http ou de https
    // -si un http a été détecté, vérifier s'il contient un quote, un double quote ou rien
    // -en fonction de son conteneur, prendre jusqu'à la fin de son url
    //   tout d'abord sauvegarder le premier index de l'url
    //   si c'est un quote ou un double quote, chercher le prochain quote ou double quote
    //   si c'est rien, alors allez jusq'au caractère espace ou au chevron fermant
    //   prendre la fin de l'url et sa longueur
    //   sauvegarder l'url dans un string
    // -ajouter le string correspondant à l'url à la liste de string

}