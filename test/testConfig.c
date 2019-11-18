//
// Created by masat on 18/11/2019.
//

#include "test.h"

static Config *pConfig = NULL;

static void testInitConfig() {
    pConfig = initConfig();
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig);

    CU_ASSERT_PTR_NULL_FATAL(pConfig->content);
    CU_ASSERT_EQUAL(pConfig->numberActions, 0);
    CU_ASSERT_EQUAL(pConfig->numberTasks, 0);

    destroyConfig(pConfig);
}

static void testRunConfig() {
    pConfig = initConfig();
    CU_ASSERT_PTR_NULL_FATAL(pConfig->content);

    runConfig(pConfig);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->content);
    destroyConfig(pConfig);
}

static void testGetPartContent() {
    pConfig = initConfig();

    runConfig(pConfig);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->actionsContent);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->tasksContent);
    destroyConfig(pConfig);
}

CU_ErrorCode configSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testConfig", NULL, NULL);

    if (NULL == CU_add_test(pSuite, "testInitConfig", testInitConfig) ||
        NULL == CU_add_test(pSuite, "testRunConfig", testRunConfig) ||
        NULL == CU_add_test(pSuite, "testGetPartContent", testGetPartContent)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}