//
// Created by masat on 01/11/2019.
//

#include "test.h"

static void testInitResource() {
    Resource
}


CU_ErrorCode resourceSpec(Cu_pSuite pSuite) {
    pSuite = CU_add_suite("testResource", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testInitResource", testInitResource))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}