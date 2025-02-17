//
// Created by masat on 01/11/2019.
//

#include "test.h"

static Resource *pResource = NULL;
static FILE *file = NULL;
static char filePath[100];
static char dirPath[100];

static void testNotInitResource() {
    pResource = initResource("http://taratata.fr", 10, 9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://tonton.fr", -1, 5);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://gougoule.fr", 2, -9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);
}

static void testInitResource() {
    pResource = initResource("http://google.jp", 5, 10);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->pRequest);
    CU_ASSERT_EQUAL(pResource->isRequest, 1);
    destroyResource(pResource);

    pResource = initResource("https://mozilla.org", 10, 11);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_STRING_EQUAL(pResource->pRequest->pUrlHelper->domainName, "mozilla.org");
    destroyResource(pResource);
}

static void testSetDirAndOutputPath() {
    char temp[100];
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", 5, 10);
    verifyPointer(pResource, "Problem initResource in testResource");
    CU_ASSERT_EQUAL(createFileResource(pResource, "toto", NULL, 0), 0);
    CU_ASSERT_EQUAL(pResource->isDirResourcePath, 1);
    CU_ASSERT_STRING_EQUAL(pResource->dirResourcePath, "toto");
    CU_ASSERT_EQUAL(pResource->isOutputPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->outputPath);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/index.txt");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    strcpy(dirPath, pResource->dirResourcePath);
    destroyResource(pResource);
    rmrf(dirPath);

    pResource = initResource("https://example.com/", 0, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(pResource, "example", NULL, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/index_scrap_0.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);

    destroyResource(pResource);
    rmrf("example");
}

static void testSetDirectoriesAndOutputPath() {
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", 5, 10);
    verifyPointer(pResource, "Problem initResource in testResource for google.com\n");
    CU_ASSERT_EQUAL(createFileResource(pResource, "toto/tata", NULL, 0), 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->outputPath);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/tata/index.txt");
    file = fopen(pResource->outputPath, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    fclose(file);
    destroyResource(pResource);
    rmrf("toto/tata");
    rmdir("toto");
}

static void testFilterUrlByContentType() {
    char *allFilesNames = NULL;
    pResource = initResource("https://example.com/", 0, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(pResource, "example/yahoo", NULL, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/yahoo/index_scrap_0.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    pResource = initResource("https://www.yahoo.fr/", 0, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(pResource, "example/yahoo", NULL, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/yahoo/index_scrap_1.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    pResource = initResource("https://google.fr/", 0, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(pResource, "example/yahoo", NULL, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/yahoo/index_scrap_2.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    strcpy(dirPath, "example/yahoo/");
    strcat(filePath, dirPath);
    strcat(filePath, ALL_FILES_NAMES);

    allFilesNames = getContentInFile(filePath, "rb");
    verifyPointer(allFilesNames, "Problem allFilesNames in testResource\n");
    CU_ASSERT(strstr(allFilesNames, "index_scrap_0") != NULL);
    CU_ASSERT(strstr(allFilesNames, "index_scrap_1") != NULL);
    CU_ASSERT(strstr(allFilesNames, "index_scrap_2") != NULL);
    free(allFilesNames);

    rmrf("example/yahoo");
    rmdir("example");
}

static void testWriteResourceInFile() {

}

CU_ErrorCode resourceSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testResource", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testNotInitResource", testNotInitResource) ||
        NULL == CU_add_test(pSuite, "testInitResource", testInitResource) ||
        NULL == CU_add_test(pSuite, "testSetDirAndOutputPath", testSetDirAndOutputPath) ||
        NULL == CU_add_test(pSuite, "testSetDirectoriesAndOutputPath", testSetDirectoriesAndOutputPath) ||
        NULL == CU_add_test(pSuite, "testFilterUrlByContentType", testFilterUrlByContentType) ||
        NULL == CU_add_test(pSuite, "testWriteResourceInFile", testWriteResourceInFile)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}