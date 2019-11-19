//
// Created by masat on 01/11/2019.
//

#include "test.h"

static Session *pSession = NULL;
static Action *pSimpleAction = NULL;

static int cleanSesionDir() {
    rmrf("Scraper");
    rmdir("Scraper");
}

static void testInitSession() {
    pSimpleAction = dummySimpleAction();
    pSession = initSession(pSimpleAction, "1st task");

    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->actionName);
    CU_ASSERT_STRING_EQUAL(pSession->actionName, "first action");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->taskName);
    CU_ASSERT_STRING_EQUAL(pSession->taskName, "1st task");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->createdDate);
    CU_ASSERT(pSession->dateSeconds > 0);

    destroyDummyAction(pSimpleAction);
    pSimpleAction = NULL;
    destroySession(pSession);
    pSession = NULL;

    pSimpleAction = dummyDepthAction();
    pSession = initSession(pSimpleAction, "2nd task");
    CU_ASSERT_STRING_EQUAL(pSession->actionName, "depth action");
    CU_ASSERT_STRING_EQUAL(pSession->taskName, "2nd task");
    destroyDummyAction(pSimpleAction);
    pSimpleAction = NULL;
    destroySession(pSession);
    pSession = NULL;
}

static void testRunSession() {
    pSimpleAction = dummySimpleAction();
    pSession = initSession(pSimpleAction, "1st task");

    runSessionAndResources(pSession, pSimpleAction);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->sessionDirPath);
    CU_ASSERT_STRING_EQUAL(pSession->sessionDirPath, "Scraper/session_0");
    CU_ASSERT_NOT_EQUAL(access("Scraper/session_all_names.txt", F_OK), -1);
    destroyDummyAction(pSimpleAction);
    pSimpleAction = NULL;
    destroySession(pSession);
    pSession = NULL;

    pSimpleAction = dummyTypesAction();
    pSession = initSession(pSimpleAction, "2nd task");
    runSessionAndResources(pSession, pSimpleAction);
    CU_ASSERT_STRING_EQUAL(pSession->sessionDirPath, "Scraper/session_1");;
}

static void testGetResource() {
    pSimpleAction = dummySimpleAction();
    pSession = initSession(pSimpleAction, "1st task");

    runSessionAndResources(pSession, pSimpleAction);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pSession->resources);

    destroyDummyAction(pSimpleAction);
    pSimpleAction = NULL;
    destroySession(pSession);
    pSession = NULL;
}

CU_ErrorCode sessionSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testSession", NULL, cleanSesionDir);

    if (NULL == CU_add_test(pSuite, "testInitSession", testInitSession) ||
        NULL == CU_add_test(pSuite, "testRunSession", testRunSession) ||
        NULL == CU_add_test(pSuite, "testGetResource", testGetResource)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}