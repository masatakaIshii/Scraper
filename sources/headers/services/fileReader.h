//
// Created by masat on 17/11/2019.
//

#ifndef SCRAPER_FILEREADER_H
#define SCRAPER_FILEREADER_H

#include <stdio.h>
#include <string.h>
#include "../common.h"
#include "../lists/listArray.h"

FILE *startFileReader(char *filePath, const char *mode);

char *getOptValue(char *filePath, char *optionName);

char *getOptValueByContent(char *content, char *optionName);

char **getAllOptValuesByOptName(char *filePath, char *optionName, int *count);

char **getOptValuesOfArrOptName(char *filePath, char *optionName, int *count);

char **getArrValuesInParenthesis(char *content, char *delimiter, int *count);

char **getArrValuesInParenthesisOfContent(char *content, char *delimiter, int *count);

//void closeFileReader(FILE *fp);

#endif //SCRAPER_FILEREADER_H
