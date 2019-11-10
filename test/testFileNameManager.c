//
// Created by masat on 10/11/2019.
//
#include "test.h"

static void testGetAvailableFileName() {

}

CU_ErrorCode fileNameManagerSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileNameManager", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetAvailableFileName", testGetAvailableFileName))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}