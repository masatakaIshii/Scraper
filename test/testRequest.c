//
// Created by masat on 17/10/2019.
//

#include "testRequest.h"

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

    if (fp != NULL) {
        fclose(fp);
    }
    if (pRequest != NULL) {
        destroyRequest(pRequest);
    }
    remove(filePath1);
    remove(filePath2);
    remove(filePath3);
    remove(filePath4);

    return 0;
}

static void checkSaveFile() {
    pRequest = initRequest("http://example.com");
    int actualResult = saveRequestInFile(pRequest, filePath1);
    destroyRequest(pRequest);
    pRequest = NULL;
    CU_ASSERT(actualResult == 0);
}

static void checkContentFile() {
    char c = ' ';
    int i = 0;

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
    while (fread(&c, sizeof(char), 1, fp), !feof(fp)) {
        CU_ASSERT_EQUAL(c, exampleFIle[i]);
        i++;
    }

    fclose(fp);
    fp = NULL;
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

static void getMimeType() {
    char contentType1[100];
    char contentType2[100];
    char contentType3[100];

    pRequest = initRequest("https://yahoo.com/");
    if (saveRequestInFile(pRequest, filePath4) != 0) {
        printf("problem save request\n");
    }
    (pRequest->mimeType != NULL) ? strcpy(contentType1, pRequest->mimeType) : strcpy(contentType1, "");
    destroyRequest(pRequest);
    pRequest = initRequest("https://blog-fr.orson.io/wp-content/uploads/2017/06/jpeg-ou-png.jpg");
    if (saveRequestInFile(pRequest, filePath4) != 0) {
        printf("problem save request\n");
    }
    (pRequest->mimeType != NULL) ? strcpy(contentType1, pRequest->mimeType) : strcpy(contentType1, "");
    destroyRequest(pRequest);

    pRequest = initRequest("https://encrypted-vtbn1.gstatic.com/video?q=tbn:ANd9GcQ_qElyG_xAPTXyC3CUx9tLom30rGaGWpWksBfe_kALSKmQnjaa");
    if (saveRequestInFile(pRequest, filePath4) != 0) {
        printf("problem save request\n");
    }
    (pRequest->mimeType != NULL) ? strcpy(contentType1, pRequest->mimeType) : strcpy(contentType1, "");
    
    CU_ASSERT_STRING_EQUAL(contentType1, "text/html");
    CU_ASSERT_STRING_EQUAL(contentType2, "image/jpeg");
    CU_ASSERT_STRING_EQUAL(contentType3, "video/mp4");
}

CU_ErrorCode requestSpec() {
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("testRequest", NULL, cleanRequest);

    if ((NULL == CU_add_test(pSuite, "checkSaveFile", checkSaveFile)) ||
        (NULL == CU_add_test(pSuite, "checkContentFile", checkContentFile)) ||
        (NULL == CU_add_test(pSuite, "getFileWithRedirectUrl", getFileWithRedirectUrl)) ||
        (NULL == CU_add_test(pSuite, "getHtmlEncodedFile", getHtmlEncodedFile)) ||
        (NULL == CU_add_test(pSuite, "getMimeType", getMimeType))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}