//
// Created by masat on 16/10/2019.
//

#include <stdio.h>
#include <CUnit/Basic.h>
#include <curl/curl.h>
#include "testRequest.h"

int main(int argc, char **argv)
{
    curl_global_init(CURL_GLOBAL_ALL);
    char suiteName[100];
    char testName[100];

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (CUE_SUCCESS != requestSpec()) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    switch (argc)
    {
        case 2:
            CU_basic_run_suite(CU_get_suite(argv[1]));
            break;
        case 3:
            strcpy(suiteName, argv[1]);
            strcpy(testName, argv[2]);
            CU_pSuite currentSuite = CU_get_suite(suiteName);
            CU_pTest currentTest = CU_get_test(currentSuite, testName);
            CU_basic_run_test(currentSuite, currentTest);
            break;
        default:
            CU_basic_run_tests();
            break;
    }

    CU_cleanup_registry();
    curl_global_cleanup();

    return CU_get_error();
}