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

static void testCheckFileExt() {
    pUrlHelper = initUrlHelper("http://www.youtube.com/video?id=16");
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://yahoo.org/index.html");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".html");
    CU_ASSERT(pUrlHelper->isFileExt == 1);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.google.fr/form.google.doc");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".doc");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://deezer.com/servietsky.funkytown.wav?petard=true&artist=lippsInc.info");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".wav");
    destroyUrlHelper(pUrlHelper);
}

static void testCheckFileNotExit() {
    pUrlHelper = initUrlHelper("http://www.youtube.com/");
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://deezer.com/servietsky.funkytown.");
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    CU_ASSERT(pUrlHelper->isFileExt == 0);
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper(
            "https://apis.google.com/_/scs/apps-static/_/js/k=oz.gapi.fr.0wWUI2yCpY8.O/m=auth2/rt=j/sv=1/d=1/ed=1/am=wQE/rs=AGLTcCO22Fl2AuKda_nx5ySnmxaf7niDMQ/cb=gapi.loaded_0");
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    CU_ASSERT_EQUAL(pUrlHelper->isFileName, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "cb=gapi.loaded_0");
    destroyUrlHelper(pUrlHelper);
}

static void testSetFileExtInFileName() {
    pUrlHelper = initUrlHelper(
            "https://apis.google.com/_/scs/apps-static/_/js/k=oz.gapi.fr.0wWUI2yCpY8.O/m=auth2/rt=j/sv=1/d=1/ed=1/am=wQE/rs=AGLTcCO22Fl2AuKda_nx5ySnmxaf7niDMQ/cb=gapi.loaded_0");
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    CU_ASSERT_EQUAL(setFileExtInFileName(pUrlHelper, "text/javascript"), 1);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".js");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "cb=gapi.loaded_0.js");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.youtube.com/");
    CU_ASSERT_EQUAL(setFileExtInFileName(pUrlHelper, "text/html"), 0);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    destroyUrlHelper(pUrlHelper);
}

static void testSetNewFileNameWhenIsNotInUrl() {
    pUrlHelper = initUrlHelper("http://www.youtube.com/");
    CU_ASSERT_EQUAL(setFileNameWhenNoOneInUrl(pUrlHelper, "index_0", "text/html"), 1);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 1);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".html");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "index_0.html");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.test.com/");
    CU_ASSERT_EQUAL(setFileNameWhenNoOneInUrl(pUrlHelper, "index_1", "application/xml"), 1);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 1);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileExt, ".xml");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "index_1.xml");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.test.com/");
    CU_ASSERT_EQUAL(setFileNameWhenNoOneInUrl(pUrlHelper, "index_1", "text/xml"), 2);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "index_1");
    destroyUrlHelper(pUrlHelper);
}


CU_ErrorCode urlHelperSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlHelper", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testCheckUrl", testCheckUrl)) ||
        (NULL == CU_add_test(pSuite, "testCheckDomainName", testCheckDomainName)) ||
        (NULL == CU_add_test(pSuite, "testCheckFileName", testCheckFileName)) ||
        (NULL == CU_add_test(pSuite, "testCheckFileExt", testCheckFileExt)) ||
        (NULL == CU_add_test(pSuite, "testCheckFileNotExit", testCheckFileNotExit)) ||
        (NULL == CU_add_test(pSuite, "testSetFileExtInFileName", testSetFileExtInFileName)) ||
        (NULL == CU_add_test(pSuite, "testSetNewFileNameWhenIsNotInUrl", testSetNewFileNameWhenIsNotInUrl))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}