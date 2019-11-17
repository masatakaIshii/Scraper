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
FILE *startFileWriter(const char *filePath, const char *mode);

void closeFileWriter(FILE *fp);


#endif //SCRAPER_FILEWRITER_H
