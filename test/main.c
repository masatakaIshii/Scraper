//
// Created by masat on 16/10/2019.
//

#include <stdio.h>
#include <CUnit/Basic.h>
#include <curl/curl.h>
#include "test.h"

void showIfSuiteAndTestArgumentsIsIncorrect(int argc, char **argv, CU_pSuite currentSuite, CU_pTest currentTest) {
    if (argc > 1) {
        if (currentSuite == NULL) {
            printf("currentSuite %s doesn't exist\n", argv[1]);
        }
        if (argc == 3) {
            if (currentTest == NULL) {
                printf("currentTest %s doesn't exist\n", argv[2]);
            }
        }
    }
}

void runSuitesAndTests(int argc, char **argv) {
    CU_pSuite currentSuite;
    CU_pTest currentTest;
    char suiteName[100];
    char testName[100];

    switch (argc) {
        case 1 :
            CU_basic_run_tests();
            break;
        case 2:
            currentSuite = CU_get_suite(argv[1]);
            CU_basic_run_suite(currentSuite);
            break;
        case 3:
            strcpy(suiteName, argv[1]);
            strcpy(testName, argv[2]);
            currentSuite = CU_get_suite(suiteName);
            currentTest = CU_get_test(currentSuite, testName);
            CU_basic_run_test(currentSuite, currentTest);
            break;
        default:
            printf("Too many arguments\n");
            return;
    }

    showIfSuiteAndTestArgumentsIsIncorrect(argc, argv, currentSuite, currentTest);
}

CU_ErrorCode listSpecs(CU_pSuite pSuite) {
    if (CUE_SUCCESS != commonSpec(pSuite) ||
        CUE_SUCCESS != requestSpec(pSuite) ||
        CUE_SUCCESS != resourceSpec(pSuite) ||
        CUE_SUCCESS != appSpec(pSuite) ||
        CUE_SUCCESS != urlHelperSpec(pSuite) ||
        CUE_SUCCESS != sessionSpec(pSuite)) {
        CU_cleanup_registry();
    }

    return CU_get_error();
}

int main(int argc, char **argv) {
    CU_pSuite pSuite = NULL;
    CU_ErrorCode result = CUE_SUCCESS;
    curl_global_init(CURL_GLOBAL_ALL);

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    result = listSpecs(pSuite);

    CU_basic_set_mode(CU_BRM_VERBOSE);

    runSuitesAndTests(argc, argv);

    CU_cleanup_registry();
    curl_global_cleanup();

    return result;
}