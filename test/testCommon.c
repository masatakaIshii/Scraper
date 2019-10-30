//
// Created by masat on 27/10/2019.
//
#include "test.h"

void static testGetIndexAfterOccurStr() {
    int length = getIndexAfterOccurStr("C'est bon les bonbons", "C'est");
    CU_ASSERT_EQUAL(length, strlen("C'est"));

    length = getIndexAfterOccurStr("numa numa yeah", "o-zone");
    CU_ASSERT_EQUAL(length, 0);

    length = getIndexAfterOccurStr("dam blue", "dam blue dabudidabuda");
    CU_ASSERT_EQUAL(length, 0);

    length = getIndexAfterOccurStr("HEYYEYAAEYAAAEYAEYAA", "YAA");
    CU_ASSERT_EQUAL(length, strlen("HEYYEYAA"));
}

void static testStrMallocCpy() {
    char *test = strMallocCpy("dada", 4);
    CU_ASSERT_STRING_EQUAL(test, "dada");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("testons", strlen("test"));
    CU_ASSERT_STRING_EQUAL(test, "test");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("test", 10);
    CU_ASSERT_STRING_EQUAL(test, "test");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("dodo", -10);
    CU_ASSERT_PTR_NULL(test);
}

CU_ErrorCode commonSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testCommon", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetIndexAfterOccurStr", testGetIndexAfterOccurStr)) ||
        (NULL == CU_add_test(pSuite, "testStrMallocCpy", testStrMallocCpy))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}