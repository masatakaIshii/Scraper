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

static void testExpandFewTimes() {
    pString = initString(1, 2);
    addString(pString, "test");
    CU_ASSERT_STRING_EQUAL(pString->content, "test");
    CU_ASSERT_EQUAL(pString->capacity, 8);
    destroyString(pString);

    pString = initString(3, 1.5);
    addString(pString, "testez");
    CU_ASSERT_STRING_EQUAL(pString->content, "testez");
    CU_ASSERT_EQUAL(pString->capacity, 9);
    destroyString(pString);

    pString = initString(2, 2);
    addString(pString, "Testez l'efficacite de l'expand de la structure String\nPour contrer tout type de fuite memoire\n");
    CU_ASSERT_STRING_EQUAL(pString->content, "Testez l'efficacite de l'expand de la structure String\nPour contrer tout type de fuite memoire\n");
    CU_ASSERT(pString->capacity > pString->count);
    destroyString(pString);

    pString = initString(100, 1.5);
    addString(pString, "https://cdn.ecosia.org/indexpage/f02934e0f082640d6bc8.js\nhttps://chrome.google.com/webstore/detail/eedlgdlajadkbbjoobobefphmfkcchfk\nhttps://cdn.ecosia.org\nhttps://s3.amazonaws.com\nhttps://cdn.ecosia.org/opensearch.xml\nhttps://cdn.ecosia.org/assets/images/ico/favicon.ico\nhttps://cdn.ecosia.org/assets/images/png/apple-touch-icon.png\nhttps://cdn.ecosia.org/manifest.json\nhttps://www.ecosia.org/?c=sv\nhttps://www.ecosia.org/?c=de\nhttps://www.ecosia.org/?c=en\nhttps://www.ecosia.org/?c=es\nhttps://www.ecosia.org/?c=fr\nhttps://www.ecosia.org/?c=it\nhttps://www.ecosia.org/?c=nl\nhttps://cdn,\344m\211/cdnorg/indexpage/71eb9e0a27a975\274p3Ze5.css\n");
    CU_ASSERT_STRING_EQUAL(pString->content, "https://cdn.ecosia.org/indexpage/f02934e0f082640d6bc8.js\nhttps://chrome.google.com/webstore/detail/eedlgdlajadkbbjoobobefphmfkcchfk\nhttps://cdn.ecosia.org\nhttps://s3.amazonaws.com\nhttps://cdn.ecosia.org/opensearch.xml\nhttps://cdn.ecosia.org/assets/images/ico/favicon.ico\nhttps://cdn.ecosia.org/assets/images/png/apple-touch-icon.png\nhttps://cdn.ecosia.org/manifest.json\nhttps://www.ecosia.org/?c=sv\nhttps://www.ecosia.org/?c=de\nhttps://www.ecosia.org/?c=en\nhttps://www.ecosia.org/?c=es\nhttps://www.ecosia.org/?c=fr\nhttps://www.ecosia.org/?c=it\nhttps://www.ecosia.org/?c=nl\nhttps://cdn,\344m\211/cdnorg/indexpage/71eb9e0a27a975\274p3Ze5.css\n");
    CU_ASSERT(pString->capacity > pString->count);
    destroyString(pString);
}

static void testSplitString() {
    char **arrStr = NULL;
    int count = 0;
    pString = initString(10, 2);
    addString(pString, "je teste\n");
    addString(pString, "tu testes\n");
    addString(pString, "il, elle, on teste\n");
    addString(pString, "nous testons\n");
    addString(pString, "vous testez\n");
    addString(pString, "ils, elles testent\n");

    arrStr = properStrSplit(pString->content, "\n", &count);
    CU_ASSERT_EQUAL_FATAL(count, 6);
    CU_ASSERT_STRING_EQUAL(arrStr[0], "je teste");
    CU_ASSERT_STRING_EQUAL(arrStr[1], "tu testes");
    CU_ASSERT_STRING_EQUAL(arrStr[2], "il, elle, on teste");
    CU_ASSERT_STRING_EQUAL(arrStr[5], "ils, elles testent");

    destroyString(pString);
    freeArrayString(arrStr, count);
}

CU_ErrorCode listCharSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testListChar", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testStringNullIfError", testStringNullIfError) ||
        NULL == CU_add_test(pSuite, "testInitString", testInitString) ||
        NULL == CU_add_test(pSuite, "testAddString", testAddString) ||
        NULL == CU_add_test(pSuite, "testExpandString", testExpandString) ||
        NULL == CU_add_test(pSuite, "testExpandFewTimes", testExpandFewTimes) ||
        NULL == CU_add_test(pSuite, "testSplitString", testSplitString)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}