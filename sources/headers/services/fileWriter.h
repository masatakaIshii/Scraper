//
// Created by masat on 17/11/2019.
//

#ifndef SCRAPER_FILEWRITER_H
#define SCRAPER_FILEWRITER_H

#include <stdio.h>
#include <string.h>

/*
 * TODO : -start stream of fileWriting
 * -write option name and option value
 * -write option name and array of value of option
 * -close stream of fileWriting
 */
FILE *startFileWriter(const char *filePath, const char *mode, const char *startStr);

int writeOptionNameAndValue(FILE *fp, const char *optionName, const char *optionValue);

int writeOptionNameAndArrayValues(FILE *fp, const char *optionName, const char **optionValues, int count);

void closeFileWriter(FILE *fp);


#endif //SCRAPER_FILEWRITER_H
