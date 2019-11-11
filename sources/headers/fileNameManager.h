//
// Created by masat on 10/11/2019.
//

#ifndef SCRAPER_FILENAMESEARCHER_H
#define SCRAPER_FILENAMESEARCHER_H

#define ALL_FILES_NAMES "all_files_names.txt"

#include <stdio.h>
#include <stdlib.h>
#include "../headers/common.h"

char *getAvailableFileName(const char *dirPath, const char *fileNameNoExt);


#endif //SCRAPER_FILENAMESEARCHER_H
