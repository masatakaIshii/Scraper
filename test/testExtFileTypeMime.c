//
// Created by masat on 07/11/2019.
//
#include "test.h"

static ListFData *list = NULL;

static void testSearchExtFileByTypeMime() {
    list = fillListFData("text/html", EXT_FILE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT(access("listExtFileMimeType.txt", F_OK) != -1);
    CU_ASSERT_EQUAL(list->numberData, 2);
    CU_ASSERT_EQUAL(list->fileDataInfo, EXT_FILE);
    destroyListFData(list);

    list = fillListFData("audio/aac", EXT_FILE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT(access("listExtFileMimeType.txt", F_OK) != -1);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".aac");
    CU_ASSERT_EQUAL(list->fileDataInfo, EXT_FILE);
    destroyListFData(list);

    list = fillListFData("application/x-7z-compressed", EXT_FILE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".7z");
    destroyListFData(list);

    list = fillListFData("text/javascript", EXT_FILE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".js");
    destroyListFData(list);

    list = fillListFData("application/javascript", EXT_FILE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".js");
    destroyListFData(list);

    list = fillListFData("toto/tata", EXT_FILE);
    CU_ASSERT_PTR_NULL_FATAL(list);

    list = fillListFData(".js", EXT_FILE);
    CU_ASSERT_PTR_NULL_FATAL(list);
}

static void testSearchMimeTypeByExtFile() {
    list = fillListFData(".html", MIME_TYPE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], "text/html");
    destroyListFData(list);

    list = fillListFData(".htm", MIME_TYPE);
    CU_ASSERT_STRING_EQUAL(list->data[0], "text/html");
    destroyListFData(list);

    list = fillListFData(".7z", MIME_TYPE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_STRING_EQUAL(list->data[0], "application/x-7z-compressed");
    destroyListFData(list);

    list = fillListFData(".3gp", MIME_TYPE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 2);
    CU_ASSERT_STRING_EQUAL(list->data[0], "video/3gpp");
    CU_ASSERT_STRING_EQUAL(list->data[1], "audio/3gpp");
    destroyListFData(list);

    list = fillListFData(".azerty", MIME_TYPE);
    CU_ASSERT_PTR_NULL_FATAL(list);

    list = fillListFData("text/html", MIME_TYPE);
    CU_ASSERT_PTR_NULL_FATAL(list);
}

CU_ErrorCode extFileTypeMimeSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testExtFileTypeMime", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testSearchExtFileByTypeMime", testSearchExtFileByTypeMime)) ||
            (NULL == CU_add_test(pSuite, "testSearchMimeTypeByExtFile", testSearchMimeTypeByExtFile))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}