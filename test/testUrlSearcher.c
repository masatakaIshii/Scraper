//
// Created by masat on 12/11/2019.
//

#include "test.h"
#include "testPageUrlDummies.h"

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

static void testWhenNoUrlInPageReturnNull() {
    char *pageWithNoUrl = getContentInFile("testPageNoUrl.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.myspace.fr", "text/html", pageWithNoUrl, &count);
    CU_ASSERT_PTR_NULL_FATAL(arrayUrl);
    free(pageWithNoUrl);
}

static void testGetUrlInPage() {
    char *pageUrl1 = getContentInFile("testPage.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", pageUrl1, &count);

    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl);
    CU_ASSERT_EQUAL(count, 1);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example");
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));

    freeArrayString(arrayUrl, count);
    arrayUrl = NULL;
    count = 0;

    free(pageUrl1);
}

static void testGetHttpUrlAndHttpsUrlInPage() {
    char *pageUrl2 = getContentInFile("testPage2.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", pageUrl2, &count);

    CU_ASSERT_EQUAL_FATAL(count, 2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[0]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example")
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[1]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[1], "http://www.iana.org/domains/example");
    CU_ASSERT(ifStringArrayContainString("http://www.iana.org/domains/example", arrayUrl, count));

    free(pageUrl2);
    count = 0;
}

static void testGetHttpUrlInTrickyHtmlPage() {
    char *pageTrickyHtml = getContentInFile("testPageTricky.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.tricky.com", "text/html", pageTrickyHtml, &count);

    CU_ASSERT_EQUAL_FATAL(count, 6);
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/favicon.ico", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/lib/w3schools_footer.js", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.tricky.com/domains/example", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://www.iana.org/domains/example", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://static.h-bid.com/sncmp/sncmp_stub.min.js", arrayUrl, count));
    CU_ASSERT(ifStringArrayContainString("https://cdn.connectad.io/connectmyusers.php", arrayUrl, count));

    free(pageTrickyHtml);
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

    if (NULL == CU_add_test(pSuite, "testWhenNoUrlInPageReturnNull", testWhenNoUrlInPageReturnNull) ||
        NULL == CU_add_test(pSuite, "testGetUrlInPage", testGetUrlInPage) ||
        NULL == CU_add_test(pSuite, "testGetHttpUrlAndHttpsUrlInPage", testGetHttpUrlAndHttpsUrlInPage) ||
        NULL == CU_add_test(pSuite, "testGetHttpUrlInTrickyHtmlPage", testGetHttpUrlInTrickyHtmlPage) ||
        NULL == CU_add_test(pSuite, "testGetUniqueHttpUrlsInArray", testGetUniqueHttpUrlsInArray)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}