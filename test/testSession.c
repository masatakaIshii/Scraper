//
// Created by masat on 01/11/2019.
//

#include "test.h"

static Session *pSession = NULL;

static void testInitSession() {
//    Action *pSimpleAction = dummySimpleAction();
//    Session *pSession = initSession(pSimpleAction);
//
//    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->action);
//    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->name);
//    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->createdDate);
//
//    destroyDummyAction(pSimpleAction);
}

CU_ErrorCode sessionSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testSession", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testInitSession", testInitSession))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}