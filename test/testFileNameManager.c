//
// Created by masat on 10/11/2019.
//
#include "test.h"

static FILE *fp = NULL;
static char *result = NULL;
static char *contentFile = NULL;
static char *check = NULL;

static void testCreateFileNamesAndGetFileName() {
    result = getAvailableName("all_files_names.txt", "", "index", "_scrap_");

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
    result = getAvailableName(NULL, "tonton", "tata_file.txt", NULL);
    CU_ASSERT_PTR_NULL_FATAL(result);
    CU_ASSERT_NOT_EQUAL(checkIfDirExist("tonton"), 1);
}

static void testAddFileNameInAllFilesNames() {
    result = getAvailableName("tata_file.txt", "tata", "tata", NULL);
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

    result = getAvailableName(manageNameFile, "", nameToAdd, btwNameNumber);
    free(result);

    result = getAvailableName(manageNameFile, "", nameToAdd, btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_esgi_1");
    contentFile = getContentInFile(manageNameFile, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\n");
    free(contentFile);
    free(result);

    result = getAvailableName(manageNameFile, "", nameToAdd, btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_esgi_2");
    contentFile = getContentInFile(manageNameFile, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\nindex_scrap_esgi_2\n");
    free(contentFile);
    free(result);

    result = getAvailableName(manageNameFile, "", "toto", btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "toto_scrap_esgi_0");
    contentFile = getContentInFile(manageNameFile, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\nindex_scrap_esgi_2\ntoto_scrap_esgi_0\n");
    free(contentFile);
    free(result);

    result = getAvailableName(manageNameFile, "", nameToAdd, btwNameNumber);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_esgi_3");
    contentFile = getContentInFile(manageNameFile, "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_PTR_NOT_EQUAL_FATAL(strlen(contentFile), 0);
    check = strstr(contentFile, result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(check);
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_esgi_0\nindex_scrap_esgi_1\nindex_scrap_esgi_2\ntoto_scrap_esgi_0\nindex_scrap_esgi_3\n");
    free(contentFile);
    free(result);

    unlink("all_created_files_names.txt");
}

static void testFilesNameManagerInDifferentDir() {
    result = getAvailableName("sessions_names", "session1", "session", "_");
    free(result);
    result = getAvailableName("sessions_names", "session1", "session", "_");
    free(result);

    result = getAvailableName("resources_names", "session2/resources", "index", "_scrap_");
    contentFile = getContentInFile("session2/resources/resources_names", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_0");
    free(result);
    free(contentFile);

    result = getAvailableName("sessions_names", "session2", "session", "_");
    contentFile = getContentInFile("session2/sessions_names", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(result, "session_0");
    CU_ASSERT_STRING_EQUAL(contentFile, "session_0\n");
    free(result);
    free(contentFile);

    result = getAvailableName("resources_names", "session2/resources", "script", "_scrap_");
    contentFile = getContentInFile("session2/resources/resources_names", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(result, "script_scrap_0");
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_0\nscript_scrap_0\n");
    free(result);
    free(contentFile);

    result = getAvailableName("sessions_names", "session1", "session", "_");
    contentFile = getContentInFile("session1/sessions_names", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(result, "session_2");
    CU_ASSERT_STRING_EQUAL(contentFile, "session_0\nsession_1\nsession_2\n");
    free(result);
    free(contentFile);

    result = getAvailableName("resources_names", "session2/resources", "index", "_scrap_");
    contentFile = getContentInFile("session2/resources/resources_names", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(result, "index_scrap_1");
    CU_ASSERT_STRING_EQUAL(contentFile, "index_scrap_0\nscript_scrap_0\nindex_scrap_1\n");
    free(result);
    free(contentFile);

    rmrf("session2/resources");
    rmrf("session2");
    rmrf("session1");
}

static void testAddNameIfNotInFilesNamesManager() {
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("", "urlManager.txt", "https://www.google.fr/"), 1);
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("", "urlManager.txt", "https://www.google.fr/analitics/"), 1);
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("", "urlManager.txt", "https://www.google.fr/"), 0);
    contentFile = getContentInFile("urlManager.txt", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(contentFile, "https://www.google.fr/\nhttps://www.google.fr/analitics/\n");
    free(contentFile);
    unlink("urlManager.txt");

    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("urlManager", "urlManager.txt", "https://www.google.fr/"), 1);
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("urlManager", "urlManager.txt", "https://www.google.fr/analitics/"), 1);
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("", "urlManager.txt", "https://www.google.fr/"), 1);
    CU_ASSERT_EQUAL(addNameIfNotInFilesNamesManager("urlManager", "urlManager.txt", "https://www.google.fr/analitics/"), 0);

    contentFile = getContentInFile("urlManager/urlManager.txt", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT_STRING_EQUAL(contentFile, "https://www.google.fr/\nhttps://www.google.fr/analitics/\n");
    free(contentFile);

    rmrf("urlManager");
    unlink("urlManager.txt");
}

static void testAddNameEvenIfFileIsEmpty() {
    FILE *fp = fopen("test.txt", "wb");

    fclose(fp);
    result = getAvailableName("test.txt", "", "tata", "_");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "tata_0");
    free(result);
    unlink("test.txt");
}

CU_ErrorCode fileNameManagerSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileNameManager", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testCreateFileNamesAndGetFileName", testCreateFileNamesAndGetFileName) ||
        NULL == CU_add_test(pSuite, "testAddIndexWhenNameToAddNoPrecise", testAddIndexWhenNameToAddNoPrecise) ||
        NULL == CU_add_test(pSuite, "testAddFileNameInAllFilesNames", testAddFileNameInAllFilesNames) ||
        NULL == CU_add_test(pSuite, "testIfFileNamesExitAddNewFileName", testIfFileNamesExitAddNewFileName) ||
        NULL == CU_add_test(pSuite, "testFilesNameManagerInDifferentDir", testFilesNameManagerInDifferentDir) ||
        NULL == CU_add_test(pSuite, "testAddNameIfNotInFilesNamesManager", testAddNameIfNotInFilesNamesManager) ||
        NULL == CU_add_test(pSuite, "testAddNameEvenIfFileIsEmpty", testAddNameEvenIfFileIsEmpty)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}