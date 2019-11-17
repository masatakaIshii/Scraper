//
// Created by masat on 17/11/2019.
//

#ifndef SCRAPER_FILEREADER_H
#define SCRAPER_FILEREADER_H

#include <stdio.h>
#include <string.h>
#include "../common.h"
#include "../lists/listArray.h"

FILE *startFileReader(const char *filePath, const char *mode);

char *getOptValue(const char *filePath, const char *optionName);

char **getAllOptValuesByOptName(const char *filePath, const char *optionName, int *count);

char **getOptValuesOfArrOptName(const char *filePath, const char *optionName, int *count);

void closeFileReader(FILE *fp);

#endif //SCRAPER_FILEREADER_H
