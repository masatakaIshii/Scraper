//
// Created by masat on 07/11/2019.
//
#include "test.h"

static ListFData *list = NULL;

static void testSearchFileExtByTypeMime() {
    list = fillListFData("text/html", FILE_EXT);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT(access("list_file_ext_mime_type.txt", F_OK) != -1);
    CU_ASSERT_EQUAL(list->numberData, 3);
    CU_ASSERT_EQUAL(list->fileDataInfo, FILE_EXT);
    destroyListFData(list);

    list = fillListFData("audio/aac", FILE_EXT);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT(access("list_file_ext_mime_type.txt", F_OK) != -1);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".aac");
    CU_ASSERT_EQUAL(list->fileDataInfo, FILE_EXT);
    destroyListFData(list);

    list = fillListFData("application/x-7z-compressed", FILE_EXT);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".7z");
    destroyListFData(list);

    list = fillListFData("text/javascript", FILE_EXT);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".js");
    destroyListFData(list);

    list = fillListFData("application/javascript", FILE_EXT);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], ".js");
    destroyListFData(list);

    list = fillListFData("toto/tata", FILE_EXT);
    CU_ASSERT_PTR_NULL_FATAL(list);

    list = fillListFData(".js", FILE_EXT);
    CU_ASSERT_PTR_NULL_FATAL(list);
}

static void testSearchMimeTypeByFileExt() {
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

    list = fillListFData(".asp", MIME_TYPE);
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_EQUAL(list->numberData, 1);
    CU_ASSERT_STRING_EQUAL(list->data[0], "text/html");
    destroyListFData(list);

    list = fillListFData(".azerty", MIME_TYPE);
    CU_ASSERT_PTR_NULL_FATAL(list);

    list = fillListFData("text/html", MIME_TYPE);
    CU_ASSERT_PTR_NULL_FATAL(list);

    list = fillListFData(".7", MIME_TYPE);
    CU_ASSERT_PTR_NULL_FATAL(list);
}

static void testIsFileExtExistsInList() {
    CU_ASSERT_EQUAL(isFileExtExistsInList(".html"), 1);
    CU_ASSERT_EQUAL(isFileExtExistsInList(".loaded_0"), 0);
    CU_ASSERT_EQUAL(isFileExtExistsInList(".ht"), 0);
}

CU_ErrorCode fileExtTypeMimeSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileExtTypeMime", NULL, NULL);

    if ((NULL == CU_add_test(pSuite, "testSearchFileExtByTypeMime", testSearchFileExtByTypeMime)) ||
        (NULL == CU_add_test(pSuite, "testSearchMimeTypeByFileExt", testSearchMimeTypeByFileExt)) ||
        (NULL == CU_add_test(pSuite, "testIsFileExtExistsInList", testIsFileExtExistsInList))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}