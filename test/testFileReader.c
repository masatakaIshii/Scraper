//
// Created by masat on 17/11/2019.
//
#include "test.h"

static FILE *fp = NULL;
static char *contentFile = NULL;

static void testInitFileReader() {
    //fp = startFileReader("tonton.txt", "rb");
}

CU_ErrorCode fileReaderSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileReader", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testInitFileReader", testInitFileReader)){

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}