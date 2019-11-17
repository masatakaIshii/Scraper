//
// Created by masat on 17/11/2019.
//

#include "test.h"

static void testStartFileWriter() {
    FILE *fp = startFileWriter("toto.txt", "rb");


}

CU_ErrorCode fileWriterSpec(CU_pSuite pSuite) {
    pSuite = CU_add_suite("testFileWriter", initManageStderr, cleanManageStderr);

    if (NULL == CU_add_test(pSuite, "testStartFileWriter", testStartFileWriter)) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    return CU_get_error();
}