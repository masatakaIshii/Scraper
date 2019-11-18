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

    fillConfig(pConfig);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->content);
    destroyConfig(pConfig);
}

static void testGetPartContent() {
    pConfig = initConfig();

    fillConfig(pConfig);
    CU_ASSERT_PTR_NULL_FATAL(pConfig->actionsContent);
    CU_ASSERT_PTR_NULL_FATAL(pConfig->tasksContent);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->actions);
    CU_ASSERT_EQUAL(pConfig->numberActions, 2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pConfig->tasks);
    CU_ASSERT_EQUAL(pConfig->numberTasks, 3);
    destroyConfig(pConfig);
}

static void testFillActions() {
    int i = 0;
    char *type[100] = {"text/javascript", "text/html", "application/javascript"};
    char *nameAction2 = "Mon deuxième site";
    pConfig = initConfig();

    fillConfig(pConfig);
    CU_ASSERT_STRING_EQUAL(pConfig->actions[0]->name, "Mon site web");
    CU_ASSERT_STRING_EQUAL(pConfig->actions[0]->url, "https://www.example.com");
    CU_ASSERT_EQUAL(pConfig->actions[0]->maxDepth, 1);
    CU_ASSERT_EQUAL(pConfig->actions[0]->versioning, 1);
    CU_ASSERT_EQUAL_FATAL(pConfig->actions[0]->numberTypes, 3);
    for (i = 0; i < pConfig->actions[0]->numberTypes; i++) {
        CU_ASSERT_STRING_EQUAL(pConfig->actions[0]->types[i], type[i]);
    }

    for (i = 0; i < (int)strlen(nameAction2); i++) {
        CU_ASSERT_EQUAL(pConfig->actions[1]->name[i], nameAction2[i]);
    }
    CU_ASSERT_STRING_EQUAL(pConfig->actions[1]->url, "https://www.google.com");
    CU_ASSERT_EQUAL(pConfig->actions[1]->maxDepth, 0);
    CU_ASSERT_EQUAL(pConfig->actions[1]->versioning, 0);
    CU_ASSERT_EQUAL_FATAL(pConfig->actions[1]->numberTypes, 0);

    destroyConfig(pConfig);
}

static void testFileTasks() {
    int i;
    int j;
    char *task0ActionsNames[100] = {"Mon site web", "Mon deuxième site"};

    pConfig = initConfig();

    fillConfig(pConfig);

    CU_ASSERT_STRING_EQUAL(pConfig->tasks[0]->name, "Ma super tache");
    CU_ASSERT_EQUAL(pConfig->tasks[0]->second, 10);
    for (i = 0; i < pConfig->tasks[0]->numberActionsNames; i++) {
        for (j = 0; j < strlen(pConfig->tasks[0]->actionsNames[i]); j++) {
            CU_ASSERT_EQUAL(pConfig->tasks[0]->actionsNames[i][j], task0ActionsNames[i][j]);
        }
    }
    destroyConfig(pConfig);
}

CU_ErrorCode configSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testConfig", NULL, NULL);

    if (NULL == CU_add_test(pSuite, "testInitConfig", testInitConfig) ||
        NULL == CU_add_test(pSuite, "testRunConfig", testRunConfig) ||
        NULL == CU_add_test(pSuite, "testGetPartContent", testGetPartContent) ||
        NULL == CU_add_test(pSuite, "testFillActions", testFillActions) ||
        NULL == CU_add_test(pSuite, "testFileTasks", testFileTasks)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}