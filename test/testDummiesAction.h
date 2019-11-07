//
// Created by masat on 01/11/2019.
//

#ifndef SCRAPER_TESTDUMMIESACTION_H
#define SCRAPER_TESTDUMMIESACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sources/headers/common.h"
#include "../sources/headers/action.h"

Action *dummySimpleAction();
void destroyDummyAction(Action *dummyAction);
Action *dummyDepthAction();

#endif //SCRAPER_TESTDUMMIESACTION_H
