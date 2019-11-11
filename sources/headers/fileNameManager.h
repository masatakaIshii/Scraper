//
// Created by masat on 10/11/2019.
//

#ifndef SCRAPER_FILENAMESEARCHER_H
#define SCRAPER_FILENAMESEARCHER_H

#define ALL_FILES_NAMES "all_files_names.txt"

#include <stdio.h>
#include <stdlib.h>
#include "../headers/common.h"

/**
 * Function to get unique name for resource that not have file name in URL
 * DEBT : fileNameNoExt is for manage the case when 2 differents url have the same file name, now it is not manage
 * @param dirPath : the directory path
 * @param fileNameNoExt : the file to add "_sc_n" where 'n' is number that is available
 * @return OK newFileName : unique file name,
 * ERROR NULL
 */
char *getAvailableFileName(const char *dirPath, const char *fileNameNoExt);

#endif //SCRAPER_FILENAMESEARCHER_H
