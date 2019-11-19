//
// Created by masat on 17/11/2019.
//
#include "test.h"

static char *result = NULL;
static char **results = NULL;
static int count = 0;
static FILE *fwp = NULL;

static void startExampleFileToRead1() {
    fwp = startFileWriter("tonton.txt", "ab", "=");

    writeOptionNameAndValue(fwp, "tata", "tonton");
    writeOptionNameAndValue(fwp, "Jacques", "Tati");

    closeFileWriter(fwp);
}
static void startExampleFileToRead2() {
    fwp = startFileWriter("tonton.txt", "ab", "=");

    writeOptionNameAndValue(fwp, "tata", "tonton");
    writeOptionNameAndValue(fwp, "Jacques", "Tati");
    writeOptionNameAndValue(fwp, "tata", "Tati");

    closeFileWriter(fwp);
}

static void startExampleFileWithArrayValue1() {
    char *arrStr[100] = {"tonton", "tata", "taratata", "tres", "thanos", "t"};

    fwp = startFileWriter("tonton.txt", "ab", "=");
    writeOptionNameAndValue(fwp, "tata", "tonton");
    writeOptionNameAndArrayValues(fwp, "tabT", (const char**)arrStr, 6);
    closeFileWriter(fwp);
}

static void startExemplaManageParenthesis() {
    char *arrStr[100] = {"tonton", "tata", "taratata", "tres", "thanos", "t"};
    fwp = startFileWriter("tata.txt", "ab", "=");
    writeOptionNameAndValue(fwp, "tata", "tonton");
    writeOptionNameAndArrayValues(fwp, "tabT", (const char**)arrStr, 6);
    writeOptionNameAndValue(fwp, "tabT", "tonton");
    closeFileWriter(fwp);
}

static void testGetOptionValue() {
    startExampleFileToRead1();

    result = getOptValue("tonton.txt", "tata");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "tonton");
    free(result);

    result = getOptValue("tonton.txt", "Jacques");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "Tati");
    free(result);

    result = getOptValue("tonton.txt", "Jacqueline");
    CU_ASSERT_PTR_NULL(result);
    unlink("tonton.txt");
}

static void testGetOptionValues() {
    startExampleFileToRead2();

    results = getAllOptValuesByOptName("tonton.txt", "tata", &count);
    CU_ASSERT_PTR_NOT_NULL_FATAL(results);
    CU_ASSERT_EQUAL(count, 2);
    CU_ASSERT_STRING_EQUAL(results[0], "tonton");
    CU_ASSERT_STRING_EQUAL(results[1], "Tati");
    freeArrayString(results, count);
    count = 0;

    results = getAllOptValuesByOptName("tonton.txt", "taratata", &count);
    CU_ASSERT_PTR_NULL_FATAL(results);
    freeArrayString(results, count);
    count = 0;

    unlink("tonton.txt");
}

static void testGetArrOptionValue() {
    startExampleFileWithArrayValue1();

    results = getOptValuesOfArrOptName("tonton.txt", "tabT", &count);
    CU_ASSERT_PTR_NOT_NULL_FATAL(results);
    CU_ASSERT_EQUAL(count, 6);
    CU_ASSERT_STRING_EQUAL(results[0], "tonton");
    CU_ASSERT_STRING_EQUAL(results[1], "tata");
    CU_ASSERT_STRING_EQUAL(results[2], "taratata");
    CU_ASSERT_STRING_EQUAL(results[3], "tres");
    CU_ASSERT_STRING_EQUAL(results[4], "thanos");
    CU_ASSERT_STRING_EQUAL(results[5], "t");
    freeArrayString(results, count);
    count = 0;
    results = NULL;
    unlink("tonton.txt");
}

static void testGetValueInParenthesis() {
    startExemplaManageParenthesis();

    results = getArrValuesInParenthesis("tata.txt", "\n", &count);
    CU_ASSERT_PTR_NOT_NULL_FATAL(results);
    CU_ASSERT_EQUAL(count, 6);
    CU_ASSERT_STRING_EQUAL(results[1], "tata");
    CU_ASSERT_STRING_EQUAL(results[5], "t");
    freeArrayString(results, count);
    count = 0;
    results = NULL;
    unlink("tata.txt");
}

CU_ErrorCode fileReaderSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileReader", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testGetOptionValue", testGetOptionValue) ||
        NULL == CU_add_test(pSuite, "testGetOptionValues", testGetOptionValues) ||
        NULL == CU_add_test(pSuite, "testGetArrOptionValue", testGetArrOptionValue) ||
        NULL == CU_add_test(pSuite, "testGetValueInParenthesis", testGetValueInParenthesis)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}