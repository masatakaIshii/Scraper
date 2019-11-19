//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_CONFIG_H
#define SCRAPER_CONFIG_H

#include <stdio.h>
#include "struct.h"
#include "common.h"
#include "app.h"

#include "task.h"
#include "services/fileReader.h"

Config *initConfig();

Action *initAction();

int fillConfig(Config *pConfig);

int runAllTasks(Config *pConfig);

void destroyConfig(Config *pConfig);

#endif //SCRAPER_CONFIG_H
