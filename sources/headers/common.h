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
 * Get number of digit of param number
 * @param number : integer to see the number of digit
 * @return OK count > 0
 * ERROR -1 : when number is less than 0
 */
int getNbrDigit(int number);

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
 * @return OK : currentStr : currentString with string that is add, <br>
 * ERROR : NULL
 */
char *strReallocCat(char *currentStr, const char *strToAdd);

/**
 * malloc and copy string with precise length
 * @param str
 * @param length
 * @return newStr : new string that is malloc
 */
char *strMallocCat(const char *str1, const char *str2);

char *strSlice(const char *string, int start, int end);

/**
 * function to get the number of occurence in string
 * @param str : string to view of there are occurence
 * @param occur : occur
 * @return result : number of occurence in string 'str'
 */
int getNbrOccurInStr(const char *str, const char *occur);

/**
 * Function to check if strin is in array of string
 * @param str
 * @param arrStr
 * @param count
 * @return OK 1 : the string is in array of string
 * ERROR 1 : the string is not in array of string
 */
int checkIfStrIsInArrStr(const char *str, const char **arrStr, int count);

/**
 * Function to get last occurrence of string
 * @param string : string to search the occurence
 * @param lastOccur : occurence to return if it's in string
 * @return OK address of char that occurrence start, <br>
 * ERROR NULL
 */
char *myStrrstr(const char *string, const char *lastOccur);

/**
 * function to split string to array of string by delimitor
 * @param str : string to copy to split in array
 * @param pCount : count of array string
 * @return
 * arrayStr : array of string
 * NULL : if str is empty
 */
char **strSplit(const char *str, const char *delimiter, int *pCount);

char **properStrSplit(const char *content, const char *delimiter, int *count);

/**
 * Free array of string
 * @param arrayStr : array of string to free
 * @param count : number of string in arrayStr
 */
void freeArrayString(char **arrayStr, int count);

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
 * Get current time in seconds
 * @return OK current time more than 0
 * ERROR -1
 */
unsigned long getCurrentTimeSec();

/**
 * Get current time verbose by given seconds unsigned long value
 * @param seconds : unsigned long value
 * @return OK strCurrentTime : verbose of currentTime
 * ERROR NULL
 */
char *getTimeToString(unsigned long seconds);

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
