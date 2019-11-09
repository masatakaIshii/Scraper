//
// Created by masat on 07/11/2019.
//

#ifndef SCRAPER_EXTFILETYPEMIME_H
#define SCRAPER_EXTFILETYPEMIME_H

#include <stdio.h>
#include <io.h>
#include "common.h"

#define LIST_EXT_FILE_TYPE_MIME "listExtFileMimeType.txt"

enum FileDataInfo{
    EXT_FILE,
    MIME_TYPE
};

typedef struct ListFileData{
    int numberData;
    char **data;
    enum FileDataInfo fileDataInfo;
} ListFData;

ListFData *fillListFData(const char *data, enum FileDataInfo dataInfo);

void destroyListFData(ListFData *pListFData);

#endif //SCRAPER_EXTFILETYPEMIME_H
