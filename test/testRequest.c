//
// Created by masat on 17/10/2019.
//

#include "test.h"

static Request *pRequest = NULL;
static FILE *fp = NULL;
static char *filePath1 = "testSaveFile1.html";
static char *filePath2 = "testSaveFile2.html";
static char *filePath3 = "yahoo1.html";
static char *filePath4 = "yahoo2.html";
static char *exampleFIle = "<!doctype html>\n"
                           "<html>\n"
                           "<head>\n"
                           "    <title>Example Domain</title>\n"
                           "\n"
                           "    <meta charset=\"utf-8\" />\n"
                           "    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />\n"
                           "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n"
                           "    <style type=\"text/css\">\n"
                           "    body {\n"
                           "        background-color: #f0f0f2;\n"
                           "        margin: 0;\n"
                           "        padding: 0;\n"
                           "        font-family: -apple-system, system-ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;\n"
                           "        \n"
                           "    }\n"
                           "    div {\n"
                           "        width: 600px;\n"
                           "        margin: 5em auto;\n"
                           "        padding: 2em;\n"
                           "        background-color: #fdfdff;\n"
                           "        border-radius: 0.5em;\n"
                           "        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);\n"
                           "    }\n"
                           "    a:link, a:visited {\n"
                           "        color: #38488f;\n"
                           "        text-decoration: none;\n"
                           "    }\n"
                           "    @media (max-width: 700px) {\n"
                           "        div {\n"
                           "            margin: 0 auto;\n"
                           "            width: auto;\n"
                           "        }\n"
                           "    }\n"
                           "    </style>    \n"
                           "</head>\n"
                           "\n"
                           "<body>\n"
                           "<div>\n"
                           "    <h1>Example Domain</h1>\n"
                           "    <p>This domain is for use in illustrative examples in documents. You may use this\n"
                           "    domain in literature without prior coordination or asking for permission.</p>\n"
                           "    <p><a href=\"https://www.iana.org/domains/example\">More information...</a></p>\n"
                           "</div>\n"
                           "</body>\n"
                           "</html>\n";

int cleanRequest(void) {
    remove(filePath1);
    remove(filePath2);
    remove(filePath3);
    remove(filePath4);
    cleanManageStderr();

    return 0;
}

static void checkWhenUrlNotExist() {
    pRequest = initRequest("https://fzoiejfoizejfoizejfozejfcdoiijaz.fr");
    CU_ASSERT(saveRequestInFile(pRequest, "errorFile.txt") != 0);
    CU_ASSERT(strlen(pRequest->errBuf) > 0);
    CU_ASSERT(access("errorFile.txt", F_OK) == -1);
    destroyRequest(pRequest);
    pRequest = initRequest("https:cdoiijaz.fr");
    CU_ASSERT(saveRequestInFile(pRequest, "errordomain.txt") != 0);
    CU_ASSERT(strlen(pRequest->errBuf) > 0);
    destroyRequest(pRequest);
}

static void checkSaveFile() {
    pRequest = initRequest("http://example.com");
    int actualResult = saveRequestInFile(pRequest, filePath1);
    destroyRequest(pRequest);
    pRequest = NULL;
    CU_ASSERT(actualResult == 0);
    CU_ASSERT(access(filePath1, F_OK) != -1);
}

static void checkContentFile() {
    int i = 0;
    char *str;

    pRequest = initRequest("http://example.com");
    if (saveRequestInFile(pRequest, filePath2) != 0) {
        printf("problem save request\n");
    }
    destroyRequest(pRequest);
    pRequest = NULL;

    fp = fopen(filePath2, "rb");
    if (fp == NULL) {
        printf("Problem fopen in testSaveFile2");
        return;
    }
    str = calloc(strlen(exampleFIle) + 1, sizeof(char));
    if (str == NULL) {
        printf("problem malloc str in checkContentFile in testRequest\n");
        exit(1);
    }
    fread(str, sizeof(char), strlen(exampleFIle), fp);
    fclose(fp);
    fp = NULL;
    CU_ASSERT_PTR_NOT_NULL_FATAL(str);
    CU_ASSERT_STRING_EQUAL(str, exampleFIle);

    free(str);
}

static void getFileWithRedirectUrl() {
    char temp[100];
    FILE *fp;
    pRequest = initRequest("https://yahoo.com/");
    if (saveRequestInFile(pRequest, filePath3) != 0) {
        printf("problem save request\n");
    }
    destroyRequest(pRequest);
    pRequest = NULL;

    fp = fopen(filePath3, "rb");
    if (fp == NULL) {
        printf("Problem open stream\n");
        exit(1);
    }
    fgets(temp, 100, fp);
    fclose(fp);

    CU_ASSERT_STRING_NOT_EQUAL(temp, "redirect");
}

static void getHtmlEncodedFile() {
    char temp[100];
    FILE *fp;
    pRequest = initRequest("https://yahoo.com/");
    if (saveRequestInFile(pRequest, filePath4) != 0) {
        printf("problem save request\n");
    }
    destroyRequest(pRequest);
    pRequest = NULL;

    fp = fopen(filePath4, "rb");
    if (fp == NULL) {
        printf("Problem openfile\n");
        exit(1);
    }
    fgets(temp, 10, fp);
    temp[10 - 1] = '\0';
    fclose(fp);

    for (int i = 0; i < 9; i++) {
        temp[i] = toupper(temp[i]);
    }

    CU_ASSERT_STRING_EQUAL(temp, "<!DOCTYPE");
}

static void checkContentType() {
    char contentType1[100];
    char contentType2[100];
    char contentType3[100];

    pRequest = initRequest("https://aurelia.io/docs/tutorials/creating-a-contact-manager#setting-up-your-machine");
    CU_ASSERT(saveRequestInFile(pRequest, filePath4) == 0);
    (pRequest->contentType != NULL) ? strcpy(contentType1, pRequest->contentType) : strcpy(contentType1, "");
    CU_ASSERT_EQUAL(strlen(contentType1), strlen("text/html"));
    CU_ASSERT_STRING_EQUAL(contentType1, "text/html");
    destroyRequest(pRequest);

    pRequest = initRequest("https://blog-fr.orson.io/wp-content/uploads/2017/06/jpeg-ou-png.jpg");
    CU_ASSERT(saveRequestInFile(pRequest, filePath4) == 0);
    (pRequest->contentType != NULL) ? strcpy(contentType2, pRequest->contentType) : strcpy(contentType2, "");
    CU_ASSERT_STRING_EQUAL(contentType2, "image/jpeg");
    destroyRequest(pRequest);

    pRequest = initRequest(
            "https://encrypted-vtbn1.gstatic.com/video?q=tbn:ANd9GcQ_qElyG_xAPTXyC3CUx9tLom30rGaGWpWksBfe_kALSKmQnjaa");
    CU_ASSERT(saveRequestInFile(pRequest, filePath4) == 0);
    (pRequest->contentType != NULL) ? strcpy(contentType3, pRequest->contentType) : strcpy(contentType3, "");
    CU_ASSERT_STRING_EQUAL(contentType3, "video/mp4");
    destroyRequest(pRequest);
}

static void notSaveWhenStatusNot200() {
    char temp[100];

    pRequest = initRequest(
            "https://clients6.google.com/drive/v2internal/viewerimpressions?key=AIzaSyAy9VVXHSpS2IJpptzYtGbLP3-3_l0aBk4&alt=json");
    CU_ASSERT(saveRequestInFile(pRequest, filePath4) != 0);
    CU_ASSERT_PTR_NULL_FATAL(pRequest->contentType);
    CU_ASSERT(access(filePath4, F_OK) != -1);

    destroyRequest(pRequest);
}

static void testGetExtFileByMimeType() {
    pRequest = initRequest("http://example.com");
    CU_ASSERT_EQUAL(getFileExtByMimeType(pRequest, "index"), 1);
    CU_ASSERT_EQUAL(pRequest->isContentType, 1);
    CU_ASSERT_STRING_EQUAL(pRequest->contentType, "text/html");
    CU_ASSERT_EQUAL(pRequest->pUrlHelper->isFileExt, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileExt, ".html");
    //rmrf("index");
    destroyRequest(pRequest);

    unlink("index/all_files_names.txt");
    rmdir("index");
}

static void testSetExtFileInFileName() {
    pRequest = initRequest(
            "https://apis.google.com/_/scs/apps-static/_/js/k=oz.gapi.fr.0wWUI2yCpY8.O/m=auth2/rt=j/sv=1/d=1/ed=1/am=wQE/rs=AGLTcCO22Fl2AuKda_nx5ySnmxaf7niDMQ/cb=gapi.loaded_0");
    CU_ASSERT_EQUAL(pRequest->pUrlHelper->isFileExt, 0);
    CU_ASSERT_EQUAL(getFileExtByMimeType(pRequest, "toto"), 1);
    CU_ASSERT_EQUAL(pRequest->pUrlHelper->isFileExt, 1);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileName, "index_scrap_0.js");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileExt);
    CU_ASSERT_EQUAL(pRequest->isContentType, 1);
    CU_ASSERT_STRING_EQUAL(pRequest->contentType, "text/javascript");
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileExt, ".js")
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileName, "index_scrap_0.js");
    rmrf("toto");
    destroyRequest(pRequest);
}

static void testGetUniqueNameWhenNoFileName() {
    pRequest = initRequest("http://example.com");
    CU_ASSERT_EQUAL(getFileExtByMimeType(pRequest, "tata"), 1);
    CU_ASSERT_EQUAL(pRequest->isContentType, 1);
    CU_ASSERT_STRING_EQUAL(pRequest->contentType, "text/html");
    CU_ASSERT_EQUAL(pRequest->pUrlHelper->isFileExt, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileExt, ".html");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileName, "index_scrap_0.html");
    destroyRequest(pRequest);

    pRequest = initRequest("http://yahoo.com");
    CU_ASSERT_EQUAL(getFileExtByMimeType(pRequest, "tata"), 1);
    CU_ASSERT_STRING_EQUAL(pRequest->contentType, "text/html");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileExt);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileExt, ".html");
    CU_ASSERT_PTR_NOT_NULL_FATAL(pRequest->pUrlHelper->fileName);
    CU_ASSERT_STRING_EQUAL(pRequest->pUrlHelper->fileName, "index_scrap_1.html");
    destroyRequest(pRequest);
    rmrf("tata");
    //deleteAllFilesNamesFiles("");
}

CU_ErrorCode requestSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testRequest", initManageStderr, cleanRequest);

    if (NULL == CU_add_test(pSuite, "checkWhenUrlNotExist", checkWhenUrlNotExist) ||
        (NULL == CU_add_test(pSuite, "checkSaveFile", checkSaveFile)) ||
        (NULL == CU_add_test(pSuite, "checkContentFile", checkContentFile)) ||
        (NULL == CU_add_test(pSuite, "getFileWithRedirectUrl", getFileWithRedirectUrl)) ||
        (NULL == CU_add_test(pSuite, "getHtmlEncodedFile", getHtmlEncodedFile)) ||
        (NULL == CU_add_test(pSuite, "checkContentType", checkContentType)) ||
        (NULL == CU_add_test(pSuite, "notSaveWhenStatusNot200", notSaveWhenStatusNot200)) ||
        (NULL == CU_add_test(pSuite, "testGetExtFileByMimeType", testGetExtFileByMimeType)) ||
        (NULL == CU_add_test(pSuite, "testSetExtFileInFileName", testSetExtFileInFileName)) ||
        (NULL == CU_add_test(pSuite, "testGetUniqueNameWhenNoFileName", testGetUniqueNameWhenNoFileName))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}