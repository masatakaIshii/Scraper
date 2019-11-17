//
// Created by masat on 17/11/2019.
//

#include "test.h"

static FILE *fp = NULL;
static char *contentFile = NULL;

static void testStartFileWriter() {
    fp = startFileWriter("toto.txt", "rb", "=");
    CU_ASSERT_PTR_NULL(fp);

    fp = startFileWriter("toto.txt", "ab", "=");
    CU_ASSERT_PTR_NOT_NULL_FATAL(fp);
    closeFileWriter(fp);

    contentFile = getContentInFile("toto.txt", "rb");
    verifyPointer(contentFile, "Problem getContentFile in testStartFileWriter\n");

    CU_ASSERT_STRING_EQUAL(contentFile, "=\n\n");

    free(contentFile);
    contentFile = NULL;

    unlink("toto.txt");
}

static void testAddOptionNameAndValue() {
    fp = startFileWriter("toto.txt", "ab", "==");

    CU_ASSERT_EQUAL(writeOptionNameAndValue(fp, "tata", "titi"), 0);
    closeFileWriter(fp);
    contentFile = getContentInFile("toto.txt", "rb");
    verifyPointer(contentFile, "Problem getContentFile in testAddOptionNameAndValue\n");

    CU_ASSERT_STRING_EQUAL(contentFile, "==\n{ tata -> titi }\n\n");
    free(contentFile);
    unlink("toto.txt");
    contentFile = NULL;
}

static void testAddOptionNameAndValues() {
    fp = startFileWriter("toto.txt", "ab", "=");
    char *arrStr1[100] = {"tonton", "tete", "teodore"};

    CU_ASSERT_EQUAL(writeOptionNameAndArrayValues(fp, "option-value",  (const char**)arrStr1, 3), 0);

    closeFileWriter(fp);
    contentFile = getContentInFile("toto.txt", "rb");
    CU_ASSERT_STRING_EQUAL(contentFile, "=\n{ option-value -> (\ntonton\ntete\nteodore\n) }\n\n");
    verifyPointer(contentFile, "Problem getContentFile in testAddOptionNameAndValues\n");
    free(contentFile);
    unlink("toto.txt");
    contentFile = NULL;

    fp = startFileWriter("toto.txt", "ab", "===");
    char *arrStr2[100] = {"tonton"};

    CU_ASSERT_EQUAL(writeOptionNameAndArrayValues(fp, "option-value",  (const char**)arrStr2, 1), 0);

    closeFileWriter(fp);
    contentFile = getContentInFile("toto.txt", "rb");
    CU_ASSERT_STRING_EQUAL(contentFile, "===\n{ option-value -> (tonton) }\n\n");
    verifyPointer(contentFile, "Problem getContentFile in testAddOptionNameAndValues\n");
    free(contentFile);
    unlink("toto.txt");
    contentFile = NULL;
}

static void testAddEqualMarkWhenRestartFileWriter() {
    fp = startFileWriter("toto.txt", "ab", "=");
    char *arrStr2[100] = {"tonton"};

    CU_ASSERT_EQUAL(writeOptionNameAndArrayValues(fp, "option-value",  (const char**)arrStr2, 1), 0);

    closeFileWriter(fp);
    contentFile = getContentInFile("toto.txt", "rb");
    CU_ASSERT_STRING_EQUAL(contentFile, "=\n{ option-value -> (tonton) }\n\n");
    verifyPointer(contentFile, "Problem getContentFile in testAddOptionNameAndValues\n");
    free(contentFile);
    contentFile = NULL;

    fp = startFileWriter("toto.txt", "ab", "=");
    CU_ASSERT_EQUAL(writeOptionNameAndValue(fp, "tata", "titi"), 0);
    closeFileWriter(fp);
    contentFile = getContentInFile("toto.txt", "rb");
    CU_ASSERT_STRING_EQUAL(contentFile, "=\n{ option-value -> (tonton) }\n\n=\n{ tata -> titi }\n\n");
    verifyPointer(contentFile, "Problem getContentFile in testAddOptionNameAndValue\n");
    free(contentFile);
    unlink("toto.txt");
    contentFile = NULL;
}

CU_ErrorCode fileWriterSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileWriter", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testStartFileWriter", testStartFileWriter) ||
        NULL == CU_add_test(pSuite, "testAddOptionNameAndValue", testAddOptionNameAndValue) ||
        NULL == CU_add_test(pSuite, "testAddOptionNameAndValues", testAddOptionNameAndValues) ||
        NULL == CU_add_test(pSuite, "testAddEqualMarkWhenRestartFileWriter", testAddEqualMarkWhenRestartFileWriter)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}