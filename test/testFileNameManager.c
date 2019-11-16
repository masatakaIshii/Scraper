//
// Created by masat on 10/11/2019.
//
#include "test.h"

static FILE *fp = NULL;
static char *result = NULL;
static char *contentFile = NULL;
static char *check = NULL;

static void testCreateFileNamesAndGetFileName() {
    result = getAvailableFileName("all_files_names.txt", "", "index", "_scrap_");

    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_0");

    contentFile = getContentInFile("all_files_names.txt", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    CU_ASSERT_EQUAL(strncmp(contentFile, "index_scrap_0", strlen("index_scrap_0")), 0);
    CU_ASSERT_NOT_EQUAL(access("all_files_names.txt", F_OK), -1);

    free(contentFile);
    free(result);
    contentFile = NULL;
    result = NULL;

    unlink("all_files_names.txt");
}

static void testAddIndexWhenNameToAddNoPrecise() {
    result = getAvailableFileName(NULL, "tonton", "tata_file.txt", NULL);
    CU_ASSERT_PTR_NULL_FATAL(result);
    CU_ASSERT_NOT_EQUAL(checkIfDirExist("tonton"), 1);
}

static void testAddFileNameInAllFilesNames() {
    result = getAvailableFileName("tata_file.txt", "tata", "tata", NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_NOT_EQUAL(access("tata/tata_file.txt", F_OK), -1);
    CU_ASSERT_STRING_EQUAL(result, "tata0");

    free(result);
    unlink("tata/tata_file.txt");
    rmdir("tata");
}

static void testIfFileNamesExitAddNewFileName() {
    char *nameToAdd = "index";
    char *manageNameFile = "all_created_files_names.txt";
    char *btwNameNumber = "_scrap_esgi_";

    result = getAvailableFileName(manageNameFile, "", nameToAdd, btwNameNumber);
    free(result);

    result = getAvailableFileName(manageNameFile, "", nameToAdd, btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_esgi_1");
    contentFile = getContentInFile(ALL_FILES_NAMES, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\n");
    free(contentFile);
    free(result);

    result = getAvailableFileName(manageNameFile, "", nameToAdd, btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_esgi_2");
    contentFile = getContentInFile(ALL_FILES_NAMES, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\nindex_scrap_esgi_2\n");
    free(contentFile);
    free(result);

    unlink("all_created_files_names.txt");
}
//
//static void testIfFileIsCreatedInDirectories() {
//    char *fileNamesPath = strMallocCat("toto/", ALL_FILES_NAMES);
//    result = getAvailableFileName("toto", NULL);
//
//    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
//    CU_ASSERT_STRING_EQUAL(result, "index_sc_0");
//    CU_ASSERT_NOT_EQUAL(access(fileNamesPath, F_OK), -1);
//    unlink(fileNamesPath);
//    rmdir("toto");
//    free(fileNamesPath);
//}

CU_ErrorCode fileNameManagerSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileNameManager", NULL, NULL);

//    if (NULL == CU_add_test(pSuite, "testCreateFileNamesAndGetFileName", testCreateFileNamesAndGetFileName) ||
//        NULL == CU_add_test(pSuite, "testAddFileNameInAllFilesNames", testAddFileNameInAllFilesNames) ||
////        NULL == CU_add_test(pSuite, "testIfFileNamesExitAddNewFileName", testIfFileNamesExitAddNewFileName) ||
////        NULL == CU_add_test(pSuite, "testIfFileIsCreatedInDirectories", testIfFileIsCreatedInDirectories)) {
    if (NULL == CU_add_test(pSuite, "testCreateFileNamesAndGetFileName", testCreateFileNamesAndGetFileName) ||
        NULL == CU_add_test(pSuite, "testAddIndexWhenNameToAddNoPrecise", testAddIndexWhenNameToAddNoPrecise) ||
        NULL == CU_add_test(pSuite, "testAddFileNameInAllFilesNames", testAddFileNameInAllFilesNames) ||
        NULL == CU_add_test(pSuite, "testIfFileNamesExitAddNewFileName", testIfFileNamesExitAddNewFileName)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}