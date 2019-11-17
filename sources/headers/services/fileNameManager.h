/*
 *  Filename    : fileNameManager.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to manage file names contain in 'all_files_names.txt' to give unique file name if the resource don't have in URL
 */

#ifndef SCRAPER_FILENAMESEARCHER_H
#define SCRAPER_FILENAMESEARCHER_H

#define ALL_FILES_NAMES "all_files_names.txt"

#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

/**
 * Function to get unique name of file depend to file names manager
 * @param fileNamesManager
 * @param dirPath
 * @param nameToAdd
 * @param btwNameAndNumber
 * @return OK newName : new available name
 * ERROR NULL
 */
char *getAvailableFileName(const char *fileNamesManager, const char *dirPath, const char *nameToAdd, const char *btwNameAndNumber);

/**
 * Function to add name in file names manager if its not include
 * @param dirPath : directory path that have file names manager
 * @param filesNamesManager : the name of file names manager
 * @param nameToCheck : the name to check if its in file names manager
 * @return OK 1 : the name is add in file name manager
 * ERROR 0 : the name is not add because it's exist alreay
 */
int addNameIfNotInFilesNamesManager(const char *dirPath, const char *filesNamesManager, const char *nameToCheck);

/**
 * Delete file name manager by given directory path and the name of file
 * @param dirPath
 * @param fileNamesManager
 * @return OK 1, ERROR 0
 */
int deleteFilesNamesManager(const char *dirPath, const char *fileNamesManager) ;
#endif //SCRAPER_FILENAMESEARCHER_H
