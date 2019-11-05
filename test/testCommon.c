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


static int checkIfDirExist(char *dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir) {
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        return 0;
    } else {
        fprintf(stderr, "Problem to open dir : %s\n", dirPath);
        return 0;
    }
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

CU_ErrorCode commonSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testCommon", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testGetIndexAfterOccurStr", testGetIndexAfterOccurStr)) ||
        (NULL == CU_add_test(pSuite, "testStrMallocCpy", testStrMallocCpy)) ||
        (NULL == CU_add_test(pSuite, "testGetCurrentDate", testGetCurrentDate)) ||
        (NULL == CU_add_test(pSuite, "testStrMallocCat", testStrMallocCat)) ||
        (NULL == CU_add_test(pSuite, "testFreePointer", testFreePointer)) ||
        (NULL == CU_add_test(pSuite, "testMkdirPCreateDirectories", testMkdirPCreateDirectories))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}