//
// Created by masat on 17/10/2019.
//

#ifndef SCRAPER_TESTREQUEST_H
#define SCRAPER_TESTREQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <CUnit/Basic.h>
#include "../sources/common.h"
#include "../sources/urlHelper.h"
#include "../sources/request.h"
#include "../sources/resource.h"
#include "../sources/session.h"
#include "../sources/app.h"
#include "testDummiesAction.h"

CU_ErrorCode commonSpec(CU_pSuite pSuite);
CU_ErrorCode requestSpec(CU_pSuite pSuite) ;
CU_ErrorCode appSpec(CU_pSuite pSuite);
CU_ErrorCode urlHelperSpec(CU_pSuite pSuite);
CU_ErrorCode sessionSpec(CU_pSuite pSuite);
CU_ErrorCode resourceSpec(CU_pSuite pSuite);

#endif //SCRAPER_TESTREQUEST_H
