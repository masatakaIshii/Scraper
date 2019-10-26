//
// Created by masat on 17/10/2019.
//

#ifndef SCRAPER_TESTREQUEST_H
#define SCRAPER_TESTREQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <CUnit/Basic.h>
#include "../sources/request.h"
#include "../sources/app.h"
#include "../sources/common.h"

CU_ErrorCode requestSpec(CU_pSuite pSuite) ;
CU_ErrorCode appSpec(CU_pSuite pSuite);
CU_ErrorCode commonSpec(CU_pSuite pSuite);

#endif //SCRAPER_TESTREQUEST_H
