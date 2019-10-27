//
// Created by masat on 26/10/2019.
//
#include "test.h"

static UrlHelper *pUrlHelper = NULL;

static void testCheckUrl() {
    pUrlHelper = initUrlHelper("h.ttoigejorg/ijhifez///iufzheiuf.hziefu");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->url, "h.ttoigejorg/ijhifez///iufzheiuf.hziefu");
    CU_ASSERT(pUrlHelper->result == UH_NAME_PB);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.google.com");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->url, "http://www.google.com");
    CU_ASSERT(pUrlHelper->result == UH_OK);
    destroyUrlHelper(pUrlHelper);
    /*CU_ASSERT(haveFileExt("https://www.google.com/dede.txt", NULL) == UH_WITH_FILE_EXT);
    CU_ASSERT(haveFileExt("https://www.toto.fr/tatatiti", NULL) == UH_WITHOUT_FILE_EXT);
    CU_ASSERT(haveFileExt("https://www.toto.fr/tatatiti/tonton.docs", NULL) == UH_WITH_FILE_EXT);
    CU_ASSERT(haveFileExt("http://www.youtube.be/dededodo?video=toto.mp4", NULL) == UH_WITHOUT_FILE_EXT);*/
}

static void testCheckDomainName() {
    pUrlHelper = initUrlHelper("http://www.google.com");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->domainName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->domainName, "www.google.com");
    CU_ASSERT(pUrlHelper->isDomainName == 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://toto.fr");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->domainName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->domainName, "toto.fr");
    CU_ASSERT(pUrlHelper->isDomainName == 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://fzieoifjzoeif");
    CU_ASSERT(pUrlHelper->isDomainName != 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.toto.titi.org/tonton.png");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->domainName, "www.toto.titi.org");
    destroyUrlHelper(pUrlHelper);
}

static void testCheckFileName() {
    pUrlHelper = initUrlHelper("http://google.com/tata.txt");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT(pUrlHelper->isFileName == 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.tata.be");
    CU_ASSERT(pUrlHelper->isFileName != 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.tata.be/");
    CU_ASSERT(pUrlHelper->isFileName != 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://tonton.jp/tati.png");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "tati.png");
    CU_ASSERT(pUrlHelper->isFileName == 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://tonton.jp/itat/tata/tete/toto/tati.png");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "tati.png");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.youtube.com/watch?v=MijmeoH9LT4");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "watch");
    destroyUrlHelper(pUrlHelper);
}

CU_ErrorCode urlHelperSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlHelper", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testCheckUrl", testCheckUrl)) ||
        (NULL == CU_add_test(pSuite, "testCheckDomainName", testCheckDomainName)) ||
        (NULL == CU_add_test(pSuite, "testCheckFileName", testCheckFileName))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}