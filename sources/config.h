//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_CONFIG_H
#define SCRAPER_CONFIG_H

#include <stdio.h>
#include "action.h"
#include "task.h"

typedef struct Config {
    Action **actions;
    Task **task;
    char *content;
} Config;

#endif //SCRAPER_CONFIG_H
