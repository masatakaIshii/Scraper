//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_TASK_H
#define SCRAPER_TASK_H

#include "action.h"

typedef struct Task {
    Action **actions;
    int numberActions;
    Option **options;
    int numberOptions;
} Task;

#endif //SCRAPER_TASK_H
