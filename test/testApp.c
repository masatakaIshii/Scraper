#include "test.h"

int cleanApp(void) {
    return 0;
}

static void changeNumberSessionApp(int number) {
    App *pApp = getApp();

    pApp->numberSession = number;
}

static void checkIfAppIsStatic() {
    App *pApp = getApp();

    changeNumberSessionApp(7);
    CU_ASSERT_EQUAL(pApp->numberSession, 7);
    changeNumberSessionApp(99);
    CU_ASSERT_EQUAL(pApp->numberSession, 99);
    free(pApp->pConfig);
    free(pApp);
}

CU_ErrorCode appSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testApp", NULL, cleanApp);

    if (NULL == CU_add_test(pSuite, "checkIfAppIsStatic", checkIfAppIsStatic)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    printf("appSpec\n");

    // if ((NULL == CU_add_test(pSuite, "checkSaveFile", checkSaveFile)) ||
    //     (NULL == CU_add_test(pSuite, "checkContentFile", checkContentFile)) ||
    //     (NULL == CU_add_test(pSuite, "getFileWithRedirectUrl", getFileWithRedirectUrl)) ||
    //     (NULL == CU_add_test(pSuite, "getHtmlEncodedFile", getHtmlEncodedFile)) ||
    //     (NULL == CU_add_test(pSuite, "checkContentType", checkContentType))) {

    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }

    return CU_get_error();
}