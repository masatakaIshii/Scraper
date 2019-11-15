//
// Created by masat on 15/11/2019.
//

#include "test.h"

static String *pString = NULL;

// testValue not correct (0 or less)
static void testStringNullIfError() {
    pString = initString(0, 1);
    CU_ASSERT_PTR_NULL_FATAL(pString);

    pString = initString(-15, 2);
    CU_ASSERT_PTR_NULL_FATAL(pString);

    pString = initString(3, 0);
    CU_ASSERT_PTR_NULL_FATAL(pString);

    pString = initString(15, 1); // because mul 1 of value is equal to value
    CU_ASSERT_PTR_NULL_FATAL(pString);
}

static void testInitString() {
    pString = initString(15, 2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pString);
    CU_ASSERT_EQUAL(pString->capacity, 15);
    CU_ASSERT_EQUAL(pString->mul, 2);
    destroyString(pString);

    pString = initString(15, 1.5);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pString);
    CU_ASSERT_EQUAL(pString->capacity, 15);
    CU_ASSERT_EQUAL(pString->mul, 1.5);
    destroyString(pString);

    pString = initString(15, 1.25);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pString);
    CU_ASSERT_EQUAL(pString->capacity, 15);
    CU_ASSERT_EQUAL(pString->mul, 1.25);
    destroyString(pString);
}

static void testAddString() {
    pString = initString(15, 1.1);
    addString(pString, "test");
    CU_ASSERT_STRING_EQUAL(pString->content, "test");
    addString(pString, "ons");
    CU_ASSERT_STRING_EQUAL(pString->content, "testons");
    destroyString(pString);

    pString = initString(20, 2);
    addString(pString, "");

    pString = initString(15, 1.1);
    addString(pString, "test\n");
    addString(pString, "ons\t\n");
    CU_ASSERT_STRING_EQUAL(pString->content, "test\nons\t\n");
    destroyString(pString);
}

static void testExpandString() {
    pString = initString(5, 2);
    addString(pString, "testons");
    CU_ASSERT_STRING_EQUAL(pString->content, "testons");
    CU_ASSERT_EQUAL(pString->capacity, 10);
    destroyString(pString);

    pString = initString(10, 2);
    addString(pString, "testons\n");
    addString(pString, "testez\n");
    CU_ASSERT_STRING_EQUAL(pString->content, "testons\ntestez\n");
    CU_ASSERT_EQUAL(pString->capacity, 20);
    destroyString(pString);

    pString = initString(4, 1.5);
    addString(pString, "test\n");
    CU_ASSERT_STRING_EQUAL(pString->content, "test\n");
    CU_ASSERT_EQUAL(pString->capacity, 6);
    destroyString(pString);

    pString = initString(4, 1.5);
    addString(pString, "test");
    CU_ASSERT_STRING_EQUAL(pString->content, "test");
    CU_ASSERT_EQUAL(pString->capacity, 6);
    destroyString(pString);
}

// test normal init if capacity and count is correct and string is correct

// test expand v1

// test if listChar can expand few time until the string to add can be add

CU_ErrorCode listCharSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testListChar", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testStringNullIfError", testStringNullIfError) ||
        NULL == CU_add_test(pSuite, "testInitString", testInitString) ||
        NULL == CU_add_test(pSuite, "testAddString", testAddString) ||
        NULL == CU_add_test(pSuite, "testExpandString", testExpandString)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}