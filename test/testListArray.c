//
// Created by masat on 12/11/2019.
//

#include "test.h"

static ListStr *listStr = NULL;

static void testInitListArray() {
    listStr = initListStr(5);

    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr);
    CU_ASSERT_EQUAL(listStr->capacity, 5);
    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr->arrStr);

    destroyListStr(listStr);
}

static void testAddStringInListArray() {
    listStr = initListStr(5);

    listStrAdd(listStr, "toto");
    CU_ASSERT_EQUAL(listStr->count, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr->arrStr[0]);
    CU_ASSERT_STRING_EQUAL(listStr->arrStr[0], "toto");

    destroyListStr(listStr);
}

static void testExceedCapacityMallocAgain() {
    listStr = initListStr(1);

    listStrAdd(listStr, "toto");
    listStrAdd(listStr, "tata");
    listStrAdd(listStr, "tonton");
    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr->arrStr[1]);

    CU_ASSERT_EQUAL(listStr->count, 3);
    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr->arrStr[2]);
    CU_ASSERT_STRING_EQUAL(listStr->arrStr[1], "tata");
    CU_ASSERT_STRING_EQUAL(listStr->arrStr[2], "tonton");
    CU_ASSERT(listStr->count <= listStr->capacity);
    CU_ASSERT_PTR_NOT_NULL_FATAL(listStr->arrStr[0]);
    CU_ASSERT_STRING_EQUAL(listStr->arrStr[0], "toto");

    destroyListStr(listStr);
}

static void testGetStringByIndex() {
    listStr = initListStr(5);

    if (!listStrAdd(listStr, "tata")) {
        fprintf(stderr, "Problem to add in listStr");
        return;
    }

    listStrAdd(listStr, "tonton");
    listStrAdd(listStr, "testons");
    listStrAdd(listStr, "testez");

    CU_ASSERT_STRING_EQUAL(listStrGet(listStr, 3), "testez");
    CU_ASSERT_STRING_EQUAL(listStrGet(listStr, 1), "tonton");
    CU_ASSERT_STRING_EQUAL(listStrGet(listStr, 0), "tata");
    CU_ASSERT_STRING_EQUAL(listStrGet(listStr, 2), "testons");

    listStrAdd(listStr, "tonton");
    listStrAdd(listStr, "testons");
    listStrAdd(listStr, "testez");

    CU_ASSERT(listStr->capacity > 5);
    CU_ASSERT(listStr->capacity >= listStr->count);

    destroyListStr(listStr);
    listStr = NULL;
}

static void testListStrErrorCases() {
    listStr = initListStr(0);
    CU_ASSERT_PTR_NULL_FATAL(listStr);

    listStr = initListStr(1);
    listStrAdd(listStr, "toto");
    CU_ASSERT_PTR_NULL_FATAL(listStrGet(listStr, 100));
    destroyListStr(listStr);
}

static void testListArrayGetArrStrAndCount() {
    char **arrStr = NULL;
    int count = 0;

    listStr = initListStr(3);
    listStrAdd(listStr, "toto");
    listStrAdd(listStr, "tata");
    listStrAdd(listStr, "titi");
    listStrAdd(listStr, "tete");
    listStrAdd(listStr, "tutu");
    listStrAdd(listStr, "tonton");
    listStrAdd(listStr, "tuctuc");
    listStrAdd(listStr, "toulouctoulouctoulouc");
    listStrAdd(listStr, "doudadada");

    arrStr = destroyListStrAndReturnArrStr(listStr, &count);
    CU_ASSERT_EQUAL(count, 9);
    CU_ASSERT_STRING_EQUAL(arrStr[0], "toto");
    CU_ASSERT_STRING_EQUAL(arrStr[1], "tata");
    CU_ASSERT_STRING_EQUAL(arrStr[2], "titi");
    CU_ASSERT_STRING_EQUAL(arrStr[3], "tete");
    CU_ASSERT_STRING_EQUAL(arrStr[4], "tutu");
    CU_ASSERT_STRING_EQUAL(arrStr[5], "tonton");
    CU_ASSERT_STRING_EQUAL(arrStr[6], "tuctuc");
    CU_ASSERT_STRING_EQUAL(arrStr[7], "toulouctoulouctoulouc");
    CU_ASSERT_STRING_EQUAL(arrStr[8], "doudadada");
    freeArrayString(arrStr, count);
}

CU_ErrorCode listArraySpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testListArray", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testInitListArray", testInitListArray) ||
        NULL == CU_add_test(pSuite, "testAddStringInListArray", testAddStringInListArray) ||
        NULL == CU_add_test(pSuite, "testExceedCapacityMallocAgain", testExceedCapacityMallocAgain) ||
        NULL == CU_add_test(pSuite, "testGetStringByIndex", testGetStringByIndex) ||
        NULL == CU_add_test(pSuite, "testListStrErrorCases", testListStrErrorCases) ||
        NULL == CU_add_test(pSuite, "testListArrayGetArrStrAndCount", testListArrayGetArrStrAndCount)){

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}
