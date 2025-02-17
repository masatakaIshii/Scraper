//
// Created by masat on 17/10/2019.
//

#ifndef SCRAPER_TESTREQUEST_H
#define SCRAPER_TESTREQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <dirent.h>
#include <CUnit/Basic.h>
#include "testShare.h"
#include "testDummiesAction.h"
#include "../sources/headers/common.h"
#include "../sources/headers/urlHelper.h"
#include "../sources/headers/request.h"
#include "../sources/headers/resource.h"
#include "../sources/headers/session.h"
#include "../sources/headers/app.h"
#include "../sources/headers/services/fileExtTypeMime.h"
#include "../sources/headers/services/fileNameManager.h"
#include "../sources/headers/urlSearcher.h"
#include "../sources/headers/lists/listArray.h"
#include "../sources/headers/lists/listChar.h"
#include "../sources/headers/services/fileWriter.h"
#include "../sources/headers/services/fileReader.h"

CU_ErrorCode commonSpec(CU_pSuite pSuite);
CU_ErrorCode requestSpec(CU_pSuite pSuite);
CU_ErrorCode appSpec(CU_pSuite pSuite);
CU_ErrorCode urlHelperSpec(CU_pSuite pSuite);
CU_ErrorCode sessionSpec(CU_pSuite pSuite);
CU_ErrorCode resourceSpec(CU_pSuite pSuite);
CU_ErrorCode fileExtTypeMimeSpec(CU_pSuite pSuite);
CU_ErrorCode fileNameManagerSpec(CU_pSuite pSuite);
CU_ErrorCode urlSearcherSpec(CU_pSuite pSuite);
CU_ErrorCode listArraySpec(CU_pSuite pSuite);
CU_ErrorCode listCharSpec(CU_pSuite pSuite);
CU_ErrorCode fileWriterSpec(CU_pSuite pSuite);
CU_ErrorCode fileReaderSpec(CU_pSuite pSuite);

#endif //SCRAPER_TESTREQUEST_H
