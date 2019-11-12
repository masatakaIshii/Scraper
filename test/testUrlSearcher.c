//
// Created by masat on 12/11/2019.
//

#include "test.h"
#include "testPageUrlDummies.h"

static char **arrayUrl = NULL;
static int count = 0;

static void testGetUrlInPage() {
    const char *pageUrl1 = getPageWithOneUrl();
    arrayUrl = getAllUrlsInPage("https://www.google.com", "text/html",pageUrl1, &count);

    CU_ASSERT_PTR_NOT_NULL_FATAL(arrayUrl);
    CU_ASSERT_EQUAL(count, 1);
    CU_ASSERT_STRING_EQUAL(arrayUrl[0], "https://static.xx.fbcdn.net/rsrc.php/v3/yr/l/0,cross/CF6sxvstdG9.css?_nc_x=lw9L9KYJoRa");

    freeArrayString(arrayUrl, count);
    arrayUrl = NULL;
    count = 0;
}

CU_ErrorCode urlSearcherSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlSearcher", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetUrlInPage", testGetUrlInPage))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}