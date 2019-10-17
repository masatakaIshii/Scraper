//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_ACTION_H
#define SCRAPER_ACTION_H

#include"option.h"

typedef struct Action {
    char *name;
    char *url;
    Option **options;
    int numberOption;
} Action;

#endif //SCRAPER_ACTION_H
