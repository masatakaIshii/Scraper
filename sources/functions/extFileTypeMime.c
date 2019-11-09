//
// Created by masat on 07/11/2019.
//

#include "../headers/extFileTypeMime.h"

static int saveListExtFileMimeTypeFile(const char *pathListExtFileMimeType) {
    FILE *fp;

    if (access(pathListExtFileMimeType, F_OK) == -1) {
        fprintf(stderr, "\nERROR : not file of list extension file and mime type.\nUninstall and reinstall the program\n");
        return -1;
    }

    return 0;
}

static ListFData *initFData() {

    ListFData *pListFData = malloc(sizeof(ListFData));
    if (pListFData == NULL) {
        return NULL;
    }

//    if (saveListExtFileMimeTypeFile(pathListExtFileMimeType) == -1){
//        fprintf(stderr, "Problem save listFileMimeTypeFile\n");
//        free(pListFData);
//        return NULL;
//    }

    pListFData->data = NULL;
    pListFData->numberData = 0;

    return pListFData;
}

static char *getExtFilesPart(const char *mimeType) {
    FILE *fp = NULL;
    char *allList = NULL;
    char *extFilePart = NULL;
    char *strMimeType = NULL;
    char *endMimeType = NULL;
    int length = 0;

    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "r");
    verifyPointer(allList, "Problem getContentInFile\n");
    strMimeType = strstr(allList, mimeType);
    if (strMimeType == NULL) {
        return NULL;
    }
    while(strMimeType > allList && *(strMimeType - 1) != '\n') {
        if (*strMimeType == ':') {
            endMimeType = strMimeType;
        }
        strMimeType -= 1;
    }

    extFilePart = strMallocCpy(strMimeType, (int)(endMimeType - strMimeType));

    return extFilePart;
}

ListFData *searchExtFileByMimeType(const char *mimeType) {
    char *extFilesPart = NULL;
    ListFData *pListFData = initFData();
    verifyPointer(pListFData, "Problem init FData");

    extFilesPart = getExtFilesPart(mimeType);
    pListFData->data = strSplit(extFilesPart, ",", &pListFData->numberData);

    free(extFilesPart);

    return pListFData;
}

void destroyListFData(ListFData *pListFData) {
    int i;
    if (pListFData->numberData > 0) {
        for (i = 0; i < pListFData->numberData; i++) {
            free(pListFData->data[i]);
        }
    }

    free(pListFData);
}