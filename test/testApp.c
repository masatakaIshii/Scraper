#include "test.h"

int cleanApp(void) {
    return 0;
}

static void changeNumberSessionApp(int number) {
    App *pApp = getApp();

    pApp->listSession->count = number;
}

static void checkIfAppIsStatic() {
    App *pApp = getApp();

    CU_ASSERT_EQUAL(pApp->listSession->capacity, 10);
    CU_ASSERT_PTR_NOT_NULL(pApp->listSession->sessions[0]);
    changeNumberSessionApp(7);
    CU_ASSERT_EQUAL(pApp->listSession->count, 7);
    changeNumberSessionApp(99);
    CU_ASSERT_EQUAL(pApp->listSession->count, 99);
    free(pApp->pConfig);
    free(pApp);
}

CU_ErrorCode appSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testApp", NULL, cleanApp);

    if (NULL == CU_add_test(pSuite, "checkIfAppIsStatic", checkIfAppIsStatic)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}