/*
 *  Filename    : fileNameManager.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to manage file names contain in 'all_files_names.txt' to give unique file name if the resource don't have in URL
 */

#ifndef SCRAPER_FILENAMESEARCHER_H
#define SCRAPER_FILENAMESEARCHER_H

#define ALL_FILES_NAMES "all_created_files_names.txt"

#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

/**
 * Function to get unique name for resource that not have file name in URL
 *
 */
char *getAvailableFileName(const char *manageNameFile, const char *dirPath, const char *nameToAdd, const char *btwNameAndNumber);

/**
 * Delete 'all_files_names.txt' by given the directory path that is contain
 * @param dirPath
 * @return OK 1, ERROR 0
 */
int  deleteAllFilesNamesFiles(const char *dirPath);
#endif //SCRAPER_FILENAMESEARCHER_H
