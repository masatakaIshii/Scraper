//
// Created by masat on 01/11/2019.
//

#include "test.h"

static Action *dummyAction = NULL;
static Resource *pResource = NULL;
static FILE *file = NULL;
static char filePath[100];
static char dirPath[100];

static void testNotInitResource() {
    dummyAction = dummySimpleAction();

    pResource = initResource("http://taratata.fr", dummyAction, 9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://tonton.fr", dummyAction, 5);
    CU_ASSERT_PTR_NULL_FATAL(pResource);

    pResource = initResource("http://gougoule.fr", dummyAction, -9);
    CU_ASSERT_PTR_NULL_FATAL(pResource);
    destroyDummyAction(dummyAction);
}

static void testInitResource() {
    dummyAction = dummySimpleAction();

    pResource = initResource("http://google.jp", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->pRequest);
    CU_ASSERT_EQUAL(pResource->isRequest, 1);
    destroyResource(pResource);

    pResource = initResource("https://mozilla.org", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_STRING_EQUAL(pResource->pRequest->pUrlHelper->domainName, "mozilla.org");
    destroyResource(pResource);
    destroyDummyAction(dummyAction);
}

static void testSetDirAndOutputPath() {
    char temp[100];
    dummyAction = dummySimpleAction();
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "toto", dummyAction, 0), 0);
    CU_ASSERT_EQUAL(pResource->isDirResourcePath, 1);
    CU_ASSERT_STRING_EQUAL(pResource->dirResourcePath, "toto");
    CU_ASSERT_EQUAL(pResource->isOutputPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->outputPath);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/index.txt");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    strcpy(dirPath, pResource->dirResourcePath);
    destroyResource(pResource);
    rmrf(dirPath);

    pResource = initResource("https://example.com/", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "example", dummyAction, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/index_scrap_0.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);

    destroyDummyAction(dummyAction);
    destroyResource(pResource);
    rmrf("example");
}

static void testSetDirectoriesAndOutputPath() {
    dummyAction = dummySimpleAction();
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "toto/tata", dummyAction, 0), 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource->outputPath);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/tata/index.txt");
    file = fopen(pResource->outputPath, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    fclose(file);
    destroyDummyAction(dummyAction);
    destroyResource(pResource);
    rmrf("toto/tata");
    rmdir("toto");
}

static void testFilterUrlByContentType() {
    char *allFilesNames = NULL;
    dummyAction = dummyTypesAction();
    pResource = initResource("https://example.com/", dummyAction, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "example/yahoo", dummyAction, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/yahoo/index_scrap_0.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    pResource = initResource("https://www.yahoo.fr/", dummyAction, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "example/yahoo", dummyAction, 0), 0);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "example/yahoo/index_scrap_1.html");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    pResource = initResource("https://google.fr/", dummyAction, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "example/yahoo", dummyAction, 0), 0);
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

    destroyDummyAction(dummyAction);
    rmrf("example/yahoo");
    rmdir("example");
}

static void testWriteResourceInFile() {

}

static void testFilterResource() {
    char *contentFile = NULL;
    dummyAction = dummyTypesAction();
    pResource = initResource("https://example.com/", dummyAction, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(createFileResource(&pResource, "example/yahoo", dummyAction, 1), -1);
    CU_ASSERT_PTR_NULL_FATAL(pResource);
    CU_ASSERT_EQUAL(access("example/yahoo/index_scrap_0.html", F_OK), -1);

    contentFile = getContentInFile("example/yahoo/all_files_names.txt", "rb");
    CU_ASSERT_PTR_NOT_NULL_FATAL(contentFile);
    CU_ASSERT(strstr(contentFile, "index_scrap_0") == NULL);
    destroyResource(pResource);
    free(contentFile);
}

CU_ErrorCode resourceSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testResource", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testNotInitResource", testNotInitResource) ||
        NULL == CU_add_test(pSuite, "testInitResource", testInitResource) ||
        NULL == CU_add_test(pSuite, "testSetDirAndOutputPath", testSetDirAndOutputPath) ||
        NULL == CU_add_test(pSuite, "testSetDirectoriesAndOutputPath", testSetDirectoriesAndOutputPath) ||
        NULL == CU_add_test(pSuite, "testFilterUrlByContentType", testFilterUrlByContentType) ||
            NULL == CU_add_test(pSuite, "testWriteResourceInFile", testWriteResourceInFile) ||
        NULL == CU_add_test(pSuite, "testFilterResource", testFilterResource)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}