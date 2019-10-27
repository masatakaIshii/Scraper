//
// Created by masat on 26/10/2019.
//
#include "test.h"


static void testIfUrlHaveFileExtension() {
    CU_ASSERT(haveFileExt("h.ttoigejorg/ijhifez///iufzheiuf.hziefu", NULL) == UH_NAME_PB);
    CU_ASSERT(haveFileExt("http://www.google.com", NULL) == UH_WITHOUT_FILE_EXT);
    CU_ASSERT(haveFileExt("https://www.google.com/dede.txt", NULL) == UH_WITH_FILE_EXT);
    CU_ASSERT(haveFileExt("https://www.toto.fr/tatatiti", NULL) == UH_WITHOUT_FILE_EXT);
    CU_ASSERT(haveFileExt("https://www.toto.fr/tatatiti/tonton.docs", NULL) == UH_WITH_FILE_EXT);
    CU_ASSERT(haveFileExt("http://www.youtube.be/dededodo?video=toto.mp4", NULL) == UH_WITHOUT_FILE_EXT);
}

CU_ErrorCode commonSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testCommon", NULL, NULL);

    if (NULL == CU_add_test(pSuite, "testGetFileNameByUrl", testIfUrlHaveFileExtension)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}