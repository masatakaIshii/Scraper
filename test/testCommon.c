//
// Created by masat on 26/10/2019.
//
#include "test.h"
int cleanCommon() {
    return 0;
}

static void testGetFileNameByUrl() {
    char *urlHttpHtml = "http://www.google.com";
    char *urlHttpsHtml = "https://www.google.com";
    //char *urlDiffExt = "https://www."

}

CU_ErrorCode commonSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testCommon", NULL, cleanCommon);

    if (NULL == CU_add_test(pSuite, "testGetFileNameByUrl", testGetFileNameByUrl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}