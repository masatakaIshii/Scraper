//
// Created by masat on 01/11/2019.
//

#include "test.h"

static Resource *pResource = NULL;

static void testNotInitResource() {
    pResource = initResource("http://taratata.fr", 10, 9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://tonton.fr", -1, 5);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://gougoule.fr", 2, -9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);
}


CU_ErrorCode resourceSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testResource", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testNotInitResource", testNotInitResource))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}