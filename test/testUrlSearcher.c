//
// Created by masat on 12/11/2019.
//

#include "test.h"
#include "testPageUrlDummies.h"

static UrlSearcher *pUrlSearcher = NULL;
static char **arrayUrl = NULL;
static int count = 0;

static int ifStringArrayContainString(char *strToCheck, char **arrStr, int numberStr) {
    int i;

    for (i = 0; i < numberStr; i++) {
        if (strncmp(strToCheck, arrStr[i], strlen(strToCheck) + 1) == 0) {
            return 1;
        }
    }
    return 0;
}

static void testInitUrlSearcher() {
    pUrlSearcher = initUrlSearcher("http://google.com", "testPage.html");

    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlSearcher);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlSearcher->protocolCom);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlSearcher->rootPath);

    destroyUrlSearcher(pUrlSearcher);
}

static void testWhenNoUrlInPageReturnNull() {
    arrayUrl = getAllUrlsInPage("https://www.myspace.fr", "text/html", "testPageNoUrl.html", &count);
    CU_ASSERT_PTR_NULL_FATAL(arrayUrl);
}

static void testGetUrlInPage() {
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", "testPage.html", &count);

    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl);
    CU_ASSERT_EQUAL(count, 1);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example");
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));

    freeArrayString(arrayUrl, count);
    arrayUrl = NULL;
    count = 0;
}

static void testGetHttpUrlAndHttpsUrlInPage() {
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", "testPage2.html", &count);

    CU_ASSERT_EQUAL_FATAL(count, 2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[0]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example")
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[1]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[1], "http://www.iana.org/domains/example");
    CU_ASSERT(ifStringArrayContainString("http://www.iana.org/domains/example", arrayUrl, count));

    count = 0;
}

static void testGetHttpUrlInTrickyHtmlPage() {
    arrayUrl = getAllUrlsInPage("https://www.tricky.com", "text/html", "testPageTricky.html", &count);

    CU_ASSERT_EQUAL_FATAL(count, 6);
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/favicon.ico", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/lib/w3schools_footer.js", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/domains/example", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://static.h-bid.com/sncmp/sncmp_stub.min.js", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://cdn.connectad.io/connectmyusers.php", arrayUrl, count));

    count = 0;
}

static void testGetUniqueHttpUrlsInArray() {
    char *pageSameUrls = getContentInFile("testPageSameUrls.html", "rb");
    arrayUrl = getAllUrlsInPage("https://test.com", "text/html", pageSameUrls, &count);

    CU_ASSERT_EQUAL_FATAL(count, 3);
    CU_ASSERT(ifStringArrayContainString("https://www.google.com", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://static.h-bid.com/sncmp/sncmp_stub.min.js", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://test.com/domains/example", arrayUrl, count));
}

CU_ErrorCode urlSearcherSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlSearcher", NULL, NULL);


//       NULL == CU_add_test(pSuite, "testGetUniqueHttpUrlsInArray", testGetUniqueHttpUrlsInArray)) {
    if (NULL == CU_add_test(pSuite, "testInitUrlSearcher", testInitUrlSearcher) ||
        NULL == CU_add_test(pSuite, "testWhenNoUrlInPageReturnNull", testWhenNoUrlInPageReturnNull) ||
        NULL == CU_add_test(pSuite, "testGetUrlInPage", testGetUrlInPage) ||
        NULL == CU_add_test(pSuite, "testGetHttpUrlAndHttpsUrlInPage", testGetHttpUrlAndHttpsUrlInPage) ||
        NULL == CU_add_test(pSuite, "testGetHttpUrlInTrickyHtmlPage", testGetHttpUrlInTrickyHtmlPage)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}