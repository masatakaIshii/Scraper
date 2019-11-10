/*
 *  Filename    : fileExtTypeMime.h
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to search file extension or mime type in listFileExtMimeType.txt and give the appropriate data.
 *                  Check also if the data linked of file extensions / mime type are correct.
 */
#ifndef SCRAPER_FILEEXTTYPEMIME_H
#define SCRAPER_FILEEXTTYPEMIME_H

#include <stdio.h>
#include <io.h>
#include "common.h"

#define LIST_EXT_FILE_TYPE_MIME "listFileExtMimeType.txt"

/**
 * @brief Enumeration to inform which data to fetch in list of file extension and mime type : <br>
 * -FILE_EXT : correspond to value to get file extension depend to one mime type<br>
 * -MIME_TYPE : correspond to value to get file extension depend to one mime type
 */
enum FileDataInfo{
    FILE_EXT, /**< correspond to value to get file extension depend to one mime type */
    MIME_TYPE /**< correspond to value to get file extension depend to one mime type */
};

/**
 * @brief the structure to fetch appropriated data in list of file extension / mime type <br>
 * -numberData : correspond to the number of data links to the near data in list of file extension / mime type <br>
 * -data : array of string correspond to file extension or mime type <br>
 * -fileDataInfo : Enumeration to inform which data to fetch in list of file extension and mime type
 */
typedef struct ListFileData{
    int numberData; /**< correspond to the number of data links to the near data in list of file extension / mime type */
    char **data; /**< array of string correspond to file extension or mime type */
    enum FileDataInfo fileDataInfo; /**< Enumeration to inform which data to fetch in list of file extension and mime type */
} ListFData;

/**
 * Fill structure depend to string 'nearData' and the dataInfo :<br>
 * -if dataInfo is FILE_EXT, the structure get extension file depend to mime type in 'nearData'<br>
 * -if dataInfo is MIME_TYPE, tje structure get mime type depend to extension file in 'nearData'
 * @param nearData : string correspond to mime type or extension file
 * @param dataInfo : enum to call the good function:<br>-get file extension<br>-get mime type
 * @return OK pointer of structure ListFData, ERROR NULL
 */
ListFData *fillListFData(const char *data, enum FileDataInfo dataInfo);

/**
 * Function to check if file extension exist in list file extension / mime type
 * @param fileExt : file extension to check
 * @return TRUE 1, FALSE 0
 */
int isFileExtExistsInList(const char *fileExt);

/**
 * Free pointer of structure ListFData and all of pointer fields
 * @param pListFData : pointer of structure ListFData
 */
void destroyListFData(ListFData *pListFData);

#endif //SCRAPER_FILEEXTTYPEMIME_H
