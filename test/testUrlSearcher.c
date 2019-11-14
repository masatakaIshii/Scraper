//
// Created by masat on 12/11/2019.
//

#include "test.h"
#include "testPageUrlDummies.h"

static char **arrayUrl = NULL;
static int count = 0;

static void testGetUrlInPage() {
    char *pageUrl1 = getContentInFile("testPage.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", pageUrl1, &count);

    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl);
    CU_ASSERT_EQUAL(count, 1);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example");

    freeArrayString(arrayUrl, count);
    arrayUrl = NULL;
    count = 0;

    free(pageUrl1);
}

static void testGetHttpUrlAndHttpsUrlInPage() {
    char *pageUrl1 = getContentInFile("testPage2.html", "rb");
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html", pageUrl1, &count);

    CU_ASSERT_EQUAL(count, 2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[0]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://www.iana.org/domains/example")
    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl[1]);
    CU_ASSERT_STRING_EQUAL(arrayUrl[1], "http://www.iana.org/domains/example");

    free(pageUrl1);
}

CU_ErrorCode urlSearcherSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlSearcher", NULL, NULL);

    if (NULL == CU_add_test(pSuite, "testGetUrlInPage", testGetUrlInPage) ||
        NULL == CU_add_test(pSuite, "testGetHttpUrlAndHttpsUrlInPage", testGetHttpUrlAndHttpsUrlInPage)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}