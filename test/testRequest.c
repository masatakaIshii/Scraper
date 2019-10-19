//
// Created by masat on 17/10/2019.
//

#include "testRequest.h"

static Request *pRequest = NULL;
static FILE *fp = NULL;
static char *filePath1 = "testSaveFile1.html";
static char *filePath2 = "testSaveFile2.html";
static char *filePath3 = "yahoo.html";
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
    if (remove(filePath1) != 0) {
        printf("\nProblem remove %s\n", filePath1);
    }
    if (remove(filePath2) != 0) {
        printf("\nProblem remove %s\n", filePath2);
    }
//    if (remove(filePath3) != 0) {
//        printf("\nProblem remove %s\n", filePath3);
//    }
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

static void redirectUrlIfResponse300() {
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

CU_ErrorCode requestSpec() {
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("testRequest", NULL, cleanRequest);

    if ((NULL == CU_add_test(pSuite, "checkSaveFile", checkSaveFile)) ||
        (NULL == CU_add_test(pSuite, "checkContentFile", checkContentFile)) ||
        (NULL == CU_add_test(pSuite, "redirectUrlIfResponse300", redirectUrlIfResponse300))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}