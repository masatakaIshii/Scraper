//
// Created by masat on 10/11/2019.
//
#include "test.h"

static FILE *fp = NULL;

static void testCreateFileNamesAndGetFileName() {
    char *result = getAvailableFileName("", NULL);
    char *contentFile = NULL;

    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_sc_0");

    contentFile = getContentInFile(ALL_FILES_NAMES, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    CU_ASSERT_EQUAL(strncmp(contentFile, "index_sc_0", strlen("index_sc_0")), 0);

    free(contentFile);
    free(result);

    unlink(ALL_FILES_NAMES);
}

static void testIfFileNamesExitAddNewFileName() {
    char *result = getAvailableFileName("", NULL);
    char *contentFile = NULL;
    char *check = NULL;

    free(result);
    result = getAvailableFileName("", NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_sc_1");
    contentFile = getContentInFile(ALL_FILES_NAMES, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_sc_0\nindex_sc_1\n");
    free(contentFile);

    result = getAvailableFileName("", NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_sc_2");
    contentFile = getContentInFile(ALL_FILES_NAMES, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_sc_0\nindex_sc_1\nindex_sc_2\n");
    free(contentFile);

    unlink(ALL_FILES_NAMES);
}

static void testIfFileIsCreatedInDirectories() {
    char *result = getAvailableFileName("toto", NULL);
    char *fileNamesPath = strMallocCat("toto/", ALL_FILES_NAMES);

    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_sc_0");
    CU_ASSERT_NOT_EQUAL(access(fileNamesPath, F_OK), -1);

    free(fileNamesPath);
    unlink(fileNamesPath);
    rmdir("toto");
}

CU_ErrorCode fileNameManagerSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileNameManager", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testCreateFileNamesAndGetFileName", testCreateFileNamesAndGetFileName)) ||
        (NULL == CU_add_test(pSuite, "testIfFileNamesExitAddNewFileName", testIfFileNamesExitAddNewFileName)) ||
            (NULL == CU_add_test(pSuite, "testIfFileIsCreatedInDirectories", testIfFileIsCreatedInDirectories))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}