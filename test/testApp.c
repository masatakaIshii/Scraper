#include "test.h"

int cleanApp(void) {
    return 0;
}

static void changeNumberSessionApp(int number) {
    App *pApp = initApp();

}

static void checkIfAppIsStatic() {
    App *pApp = initApp();

    CU_ASSERT_EQUAL(runApp(pApp), 0);

    destroyConfig(pApp->pConfig);

}

CU_ErrorCode appSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testApp", NULL, cleanApp);

    if (NULL == CU_add_test(pSuite, "checkIfAppIsStatic", checkIfAppIsStatic)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}
