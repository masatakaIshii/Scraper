/*
 *  Filename    : common.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#ifndef SCRAPER_COMMON_H
#define SCRAPER_COMMON_H
#include <curl/curl.h>
#include <dirent.h>
#include "struct.h"
#include "app.h"

/**
 * verify the pointer and if its null, show message and quit program with exit status '1'
 * @param pointer
 * @param message
 */
void verifyPointer(void *pointer, const char *message);

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return
 */
char *strMallocCpy(const char *str, int length);

/**
 * Function to realloc currentStr with string to add and concat
 * @param currentStr : current string to realloc
 * @param strToAdd : string to add in current string
 * @return currentStr : currentString with string that is add
 */
char *strReallocCat(char *currentStr, const char *strToAdd);

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return newStr : new string that is malloc
 */
char *strMallocCat(const char *str1, const char *str2);

/**
 * function to get the number of occurence in string
 * @param str : string to view of there are occurence
 * @param occur : occur
 * @return result : number of occurence in string 'str'
 */
int getNbrOccurInStr(const char *str, const char *occur);

/**
 * function to split string to array of string by delimitor
 * @param str : string to copy to split in array
 * @param pCount : count of array string
 * @return
 * arrayStr : array of string
 * NULL : if str is empty
 */
char **strSplit(const char *str, const char *delimiter, int *pCount);

/**
 * get index of array of char strCheck after the occurrence of string strOccur
 * @param strCheck : string to search if there are occurrence
 * @param strOccur : string correspond to occurrence
 * @return index : index after occurrence strOccur
 */
int getIndexAfterOccurStr(const char *strCheck, const char *strOccur);

/**
 * get content of file content in filePath
 * @param filePath
 * @param mode : can be 'r' or 'rb'
 * @return
 */
char *getContentInFile(const char *filePath, const char *mode);

/**
 * Get current time format "strDate strMonth intDate intHours:intMin:intSec intYears"
 * Example : "Sun Oct 01 13:12:00 2019"
 * @return string content current time
 */
char *getCurrentTime();

/**
 * destroy pointer if boolean of field is == 1, and affect boolean to 0
 * @param pointer : the pointer to free
 * @param isMalloc : variable of boolean to check if pointer is already malloc and put to 0
 */
void freePointer(void **pointer, short *isMalloc);

/**
 * function to create directories recursively like mkdirP
 * @param dirPath
 * @return
 * 0 : correct value and directories created
 * -1 : error value, because of directory path wrong value
 */
int mkdirP(const char *dirPath);

/**
 * Function to verify if the directory exist
 * @param dirPath
 * @return
 * 1 : directory that have dirPath value exist
 * 0 : directory that is dirPath not exist
 */
int checkIfDirExist(char *dirPath);

#endif //SCRAPER_COMMON_H
