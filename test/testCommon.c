//
// Created by masat on 27/10/2019.
//
#include "test.h"

static void testGetIndexAfterOccurStr() {
    int length = getIndexAfterOccurStr("C'est bon les bonbons", "C'est");
    CU_ASSERT_EQUAL(length, strlen("C'est"));

    length = getIndexAfterOccurStr("numa numa yeah", "o-zone");
    CU_ASSERT_EQUAL(length, 0);

    length = getIndexAfterOccurStr("dam blue", "dam blue dabudidabuda");
    CU_ASSERT_EQUAL(length, 0);

    length = getIndexAfterOccurStr("HEYYEYAAEYAAAEYAEYAA", "YAA");
    CU_ASSERT_EQUAL(length, strlen("HEYYEYAA"));
}

static void testStrMallocCpy() {
    char *test = strMallocCpy("dada", 4);
    CU_ASSERT_STRING_EQUAL(test, "dada");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("testons", strlen("test"));
    CU_ASSERT_STRING_EQUAL(test, "test");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("test", 10);
    CU_ASSERT_STRING_EQUAL(test, "test");
    CU_ASSERT_EQUAL(strlen(test), 4);
    free(test);

    test = strMallocCpy("dodo", -10);
    CU_ASSERT_PTR_NULL(test);
}

static void testGetCurrentDate() {
    char *currentDate = getCurrentTime();
    time_t expected = time(NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(currentDate);
    CU_ASSERT_STRING_EQUAL(currentDate, ctime(&expected));
    free(currentDate);
}

static void testStrMallocCat() {
    char *str1 = "testons";
    char *str2 = " son efficacite";
    char *result = NULL;
    result = strMallocCat(str1, str2);

    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "testons son efficacite");
    free(result);

    result = strMallocCat("tonton", "");
    CU_ASSERT_STRING_EQUAL(result, "tonton");
    CU_ASSERT(strlen(result) == strlen("tonton"));
    free(result);

    result = strMallocCat("", "tonton");
    CU_ASSERT_STRING_EQUAL(result, "tonton");
    CU_ASSERT(strlen(result) == strlen("tonton"));
    free(result);

    result = strMallocCat("", "");
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    free(result);
}

struct TestStr {
    char *str;
    int isStr;
};

static void testFreePointer() {
    int *arrayInt = calloc(5, sizeof(int));
    int isArrayInt = 1;
    struct TestStr *testStr = malloc(sizeof(struct TestStr));

    freePointer((void **) &arrayInt, (short *) &isArrayInt);
    CU_ASSERT_EQUAL(isArrayInt, 0);
    CU_ASSERT_PTR_NULL_FATAL(arrayInt);

    testStr->str = calloc(strlen("titi") + 1, sizeof(char));
    strcpy(testStr->str, "titi");
    testStr->isStr = 1;

    freePointer((void **) &testStr->str, (short *) &testStr->isStr);

    CU_ASSERT_EQUAL(testStr->isStr, 0);
    CU_ASSERT_PTR_NULL_FATAL(testStr->str);

    free(testStr);

    freePointer((void **) &arrayInt, (short *) &isArrayInt);
    CU_ASSERT_EQUAL(isArrayInt, 0);
}

static void testMkdirPCreateDirectories() {

    CU_ASSERT_EQUAL(mkdirP("toto"), 0);
    CU_ASSERT_EQUAL(checkIfDirExist("toto"), 1);
    rmdir("toto");

    CU_ASSERT_EQUAL(mkdirP("tata/toto"), 0);
    CU_ASSERT_EQUAL(checkIfDirExist("tata"), 1);
    CU_ASSERT_EQUAL(checkIfDirExist("tata/toto"), 1);
    rmdir("tata/toto");
    rmdir("tata");

    CU_ASSERT_EQUAL(mkdirP("la tata/le tonton"), 0);
    CU_ASSERT_EQUAL(checkIfDirExist("la tata"), 1);
    CU_ASSERT_EQUAL(checkIfDirExist("la tata/le tonton"), 1);
    rmdir("la tata/le tonton");
    rmdir("la tata");

    CU_ASSERT_EQUAL(mkdirP("////"), -1);

    CU_ASSERT_EQUAL(mkdirP("tonton?/non|tata"), -1);
}

static void testMkdirPNotEraseExitContent() {
    mkdir("tata");
    mkdir("tata/toto");
    FILE *fp = fopen("tata/file.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(fp);
    fclose(fp);
    CU_ASSERT_EQUAL(mkdirP("tata"), 0);
    CU_ASSERT_EQUAL(checkIfDirExist("tata/toto"), 1);
    CU_ASSERT_NOT_EQUAL(access("tata/file.txt", F_OK), -1);
    unlink("tata/file.txt");
    rmdir("tata/toto");
    rmdir("tata");
}

static void testGetContentFile() {
    char *test1 = "test.testons\n";
    char *test2 = "tata\n"
                  "tititontons\n";
    char *result = NULL;
    FILE *fp = fopen("test.txt", "wb");
    verifyPointer(fp, "Problem open file in testGetContentFile\n");

    fprintf(fp, "%s", test1);
    fclose(fp);

    result = getContentInFile("test.txt", "rb");
    CU_ASSERT_EQUAL(strlen(result), strlen(test1));
    CU_ASSERT_STRING_EQUAL(result, test1);
    free(result);

    result = getContentInFile("test.txt", "a");
    CU_ASSERT_PTR_NULL_FATAL(result);
    result = getContentInFile("test.txt", "w");
    CU_ASSERT_PTR_NULL_FATAL(result);
    result = getContentInFile("tonton.txt", "r");
    CU_ASSERT_PTR_NULL_FATAL(result);

    fp = fopen("tonton.txt", "wb");
    verifyPointer(fp, "Problem open file tonton.txt\n");

    fwrite(test2, sizeof(char), strlen(test2), fp);
    fclose(fp);

    result = getContentInFile("tonton.txt", "rb");
    CU_ASSERT_EQUAL(strlen(result), strlen(test2));
    CU_ASSERT_STRING_EQUAL(result, test2);
    free(result);
    remove("test.txt");
    remove("tonton.txt");
}

CU_ErrorCode commonSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testCommon", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetIndexAfterOccurStr", testGetIndexAfterOccurStr)) ||
        (NULL == CU_add_test(pSuite, "testStrMallocCpy", testStrMallocCpy)) ||
        (NULL == CU_add_test(pSuite, "testGetCurrentDate", testGetCurrentDate)) ||
        (NULL == CU_add_test(pSuite, "testStrMallocCat", testStrMallocCat)) ||
        (NULL == CU_add_test(pSuite, "testFreePointer", testFreePointer)) ||
        (NULL == CU_add_test(pSuite, "testMkdirPCreateDirectories", testMkdirPCreateDirectories)) ||
        (NULL == CU_add_test(pSuite, "testMkdirPNotEraseExitContent", testMkdirPNotEraseExitContent)) ||
        (NULL == CU_add_test(pSuite, "testGetContentFile", testGetContentFile))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}