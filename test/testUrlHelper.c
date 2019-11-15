//
// Created by masat on 26/10/2019.
//
#include "test.h"

static UrlHelper *pUrlHelper = NULL;
static FILE *fpError = NULL;

static void testCheckUrl() {
    pUrlHelper = initUrlHelper("h.ttoigejorg/ijhifez///iufzheiuf.hziefu");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper);
    CU_ASSERT_EQUAL(pUrlHelper->isUrl, 0);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->url);

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
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper);
    CU_ASSERT_EQUAL(pUrlHelper->isUrl, 0);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->url);

    pUrlHelper = initUrlHelper("http://www.toto.titi.org/tonton.png");
    CU_ASSERT_STRING_EQUAL(pUrlHelper->domainName, "www.toto.titi.org");
    destroyUrlHelper(pUrlHelper);
}

static void testAbsPath() {
    pUrlHelper = initUrlHelper("http://google.com/");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://www.google.com");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://google.fr/translate");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/translate/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("http://google.fr/translate/");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/translate/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.aol.org/main/about/information");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/main/about/information/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.deezer.com/search/hardtech?oijzeofijzo&oijzefoij&oijoirfmoer");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/search/hardtech/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.deezer.com/search/hardtech/sample.mp3");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/search/hardtech/");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper("https://www.example.com/example.html");
    CU_ASSERT_EQUAL(pUrlHelper->isAbsPath, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->absPath);
    CU_ASSERT_EQUAL(strlen(pUrlHelper->absPath), 1);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->absPath, "/");
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
    CU_ASSERT(pUrlHelper->isFileName != 1);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->fileName);
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

    pUrlHelper = initUrlHelper(
            "https://apis.google.com/_/scs/apps-static/_/js/k=oz.gapi.fr.0wWUI2yCpY8.O/m=auth2/rt=j/sv=1/d=1/ed=1/am=wQE/rs=AGLTcCO22Fl2AuKda_nx5ySnmxaf7niDMQ/cb=gapi.loaded_0");
    CU_ASSERT(pUrlHelper->isFileName != 1);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->fileExt);
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
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    CU_ASSERT(pUrlHelper->isFileExt == 0);
    destroyUrlHelper(pUrlHelper);
}

static void testSetFileExtInFileName() {


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
    CU_ASSERT_EQUAL(setFileNameWhenNoOneInUrl(pUrlHelper, "index_1", "text/xml"), 2); // mime type that is not in list
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    CU_ASSERT_PTR_NULL_FATAL(pUrlHelper->fileExt);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "index_1");
    destroyUrlHelper(pUrlHelper);

    pUrlHelper = initUrlHelper(
            "https://apis.google.com/_/scs/apps-static/_/js/k=oz.gapi.fr.0wWUI2yCpY8.O/m=auth2/rt=j/sv=1/d=1/ed=1/am=wQE/rs=AGLTcCO22Fl2AuKda_nx5ySnmxaf7niDMQ/cb=gapi.loaded_0");
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 0);
    CU_ASSERT_PTR_NULL(pUrlHelper->fileExt);
    CU_ASSERT_EQUAL(setFileNameWhenNoOneInUrl(pUrlHelper, "created_name_scrap_2", "text/javascript"), 1);
    CU_ASSERT_EQUAL(setFileExtInFileName(pUrlHelper, "text/javascript"), 1);
    CU_ASSERT_EQUAL(pUrlHelper->isFileExt, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pUrlHelper->fileName, "created_name_scrap_2.js");
    destroyUrlHelper(pUrlHelper);
}

static void testGetUrlWithAbsPath() {
    char *urlAbsPath = NULL;
    pUrlHelper = initUrlHelper("https://www.google.com/");
    verifyPointer(pUrlHelper, "ERROR in testUrlHelper : Problem initUrlHelper in testGetUrlWithAbsPath\n");
    urlAbsPath = getUrlWithAbsPath(pUrlHelper);
    CU_ASSERT_PTR_NOT_NULL_FATAL(urlAbsPath);
    CU_ASSERT_EQUAL(strlen(urlAbsPath), strlen("https://www.google.com/"));
    CU_ASSERT_STRING_EQUAL(urlAbsPath, "https://www.google.com/")
    destroyUrlHelper(pUrlHelper);
    free(urlAbsPath);
    urlAbsPath = NULL;

    pUrlHelper = initUrlHelper("https://www.google.com");
    verifyPointer(pUrlHelper, "ERROR in testUrlHelper : Problem initUrlHelper in testGetUrlWithAbsPath\n");
    urlAbsPath = getUrlWithAbsPath(pUrlHelper);
    CU_ASSERT_PTR_NOT_NULL_FATAL(urlAbsPath);
    CU_ASSERT_EQUAL(strlen(urlAbsPath), strlen("https://www.google.com/"));
    CU_ASSERT_STRING_EQUAL(urlAbsPath, "https://www.google.com/")
    destroyUrlHelper(pUrlHelper);
    free(urlAbsPath);
    urlAbsPath = NULL;

    pUrlHelper = initUrlHelper("https://www.deezer/albums/summer/");
    verifyPointer(pUrlHelper, "ERROR in testUrlHelper : Problem initUrlHelper in testGetUrlWithAbsPath\n");
    urlAbsPath = getUrlWithAbsPath(pUrlHelper);
    CU_ASSERT_PTR_NOT_NULL_FATAL(urlAbsPath);
    CU_ASSERT_EQUAL(strlen(urlAbsPath), strlen("https://www.deezer/albums/summer/"));
    CU_ASSERT_STRING_EQUAL(urlAbsPath, "https://www.deezer/albums/summer/")
    destroyUrlHelper(pUrlHelper);
    free(urlAbsPath);
    urlAbsPath = NULL;

    pUrlHelper = initUrlHelper("https://www.w3schools.com/tags/att_meta_content.asp");
    verifyPointer(pUrlHelper, "ERROR in testUrlHelper : Problem initUrlHelper in testGetUrlWithAbsPath\n");
    urlAbsPath = getUrlWithAbsPath(pUrlHelper);
    CU_ASSERT_PTR_NOT_NULL_FATAL(urlAbsPath);
    CU_ASSERT_EQUAL(strlen(urlAbsPath), strlen("https://www.w3schools.com/tags/"));
    CU_ASSERT_STRING_EQUAL(urlAbsPath, "https://www.w3schools.com/tags/")
    destroyUrlHelper(pUrlHelper);
    free(urlAbsPath);
}

CU_ErrorCode urlHelperSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testUrlHelper", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testCheckUrl", testCheckUrl) ||
        NULL == CU_add_test(pSuite, "testCheckDomainName", testCheckDomainName) ||
        NULL == CU_add_test(pSuite, "testAbsPath", testAbsPath) ||
        NULL == CU_add_test(pSuite, "testCheckFileName", testCheckFileName) ||
        NULL == CU_add_test(pSuite, "testCheckFileExt", testCheckFileExt) ||
        NULL == CU_add_test(pSuite, "testCheckFileNotExit", testCheckFileNotExit) ||
        NULL == CU_add_test(pSuite, "testSetFileExtInFileName", testSetFileExtInFileName) ||
        NULL == CU_add_test(pSuite, "testSetNewFileNameWhenIsNotInUrl", testSetNewFileNameWhenIsNotInUrl) ||
        NULL == CU_add_test(pSuite, "testGetUrlWithAbsPath", testGetUrlWithAbsPath)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}