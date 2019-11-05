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

    //TODO : test dir and output paths
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", 5, 10);
    verifyPointer(pResource, "Problem initResource in testResource");
    CU_ASSERT_EQUAL(createFileResource(pResource, "toto"), 0);
    CU_ASSERT_EQUAL(pResource->isDirResourcePath, 1);
    CU_ASSERT_STRING_EQUAL(pResource->dirResourcePath, "toto");
    CU_ASSERT_EQUAL(pResource->isOutputPath, 1);
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/index.txt");
    CU_ASSERT_NOT_EQUAL(access(pResource->outputPath, F_OK), -1);   
    strcpy(filePath, pResource->outputPath);
    strcpy(dirPath, pResource->dirResourcePath);
    destroyResource(pResource);
    rmdir(dirPath);

    pResource = initResource("https://example.com/", 0, 0);
    verifyPointer(pResource, "Problem initResource of example.com in testResource");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pResource);
    CU_ASSERT_NOT_EQUAL(createFileResource(pResource, "example"), 0);
    CU_ASSERT_EQUAL(access(pResource->outputPath, F_OK), -1);
    destroyResource(pResource);

    // TODO : test if file is save in directory
}

static void testSetDirectoriesAndOutputPath() {
    pResource = initResource("https://static.openfoodfacts.org/data/delta/index.txt", 5, 10);
    verifyPointer(pResource, "Problem initResource in testResource for google.com\n");
    CU_ASSERT_EQUAL(createFileResource(pResource, "toto/tata"), 0); // TODO : manage maybe in Common, for create directory recursively like mkdir -p
    CU_ASSERT_STRING_EQUAL(pResource->outputPath, "toto/tata/index.txt");
    file = fopen(pResource->outputPath, "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(file);

    fclose(file);
    destroyResource(pResource);
}

CU_ErrorCode resourceSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testResource", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testNotInitResource", testNotInitResource)) ||
        (NULL == CU_add_test(pSuite, "testInitResource", testInitResource)) ||
        (NULL == CU_add_test(pSuite, "testSetDirAndOutputPath", testSetDirAndOutputPath)) ||
        (NULL == CU_add_test(pSuite, "testSetDirectoriesAndOutputPath", testSetDirectoriesAndOutputPath))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}