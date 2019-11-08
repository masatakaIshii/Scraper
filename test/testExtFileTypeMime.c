//
// Created by masat on 07/11/2019.
//
#include "test.h"

static void testGetLineByTypeMime() {
    ListFData *list = searchExtFileByMimeType("toto/tata");

    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT(access("listExtFileMimeType.txt", F_OK) != -1);

    destroyListFData(list);
}

CU_ErrorCode extFileTypeMimeSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testExtFileTypeMime", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetLineByTypeMime", testGetLineByTypeMime))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}