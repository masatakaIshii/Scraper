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
#include "../sources/headers/common.h"
#include "../sources/headers/urlHelper.h"
#include "../sources/headers/request.h"
#include "../sources/headers/resource.h"
#include "../sources/headers/session.h"
#include "../sources/headers/app.h"
#include "testDummiesAction.h"

CU_ErrorCode commonSpec(CU_pSuite pSuite);
CU_ErrorCode requestSpec(CU_pSuite pSuite) ;
CU_ErrorCode appSpec(CU_pSuite pSuite);
CU_ErrorCode urlHelperSpec(CU_pSuite pSuite);
CU_ErrorCode sessionSpec(CU_pSuite pSuite);
CU_ErrorCode resourceSpec(CU_pSuite pSuite);

#endif //SCRAPER_TESTREQUEST_H
