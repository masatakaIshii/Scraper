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
 * DEBT : fileNameNoExt is for manage the case when 2 differents url have the same file name, now it is not manage
 * @param dirPath : the directory path
 * @param fileNameNoExt : the file to add "_sc_n" where 'n' is number that is available
 * @return OK newFileName : unique file name,
 * ERROR NULL
 */
char *getAvailableFileName(const char *dirPath, const char *fileNameNoExt);

/**
 * Delete 'all_files_names.txt' by given the directory path that is contain
 * @param dirPath
 * @return OK 1, ERROR 0
 */
int  deleteAllFilesNamesFiles(const char *dirPath);
#endif //SCRAPER_FILENAMESEARCHER_H
