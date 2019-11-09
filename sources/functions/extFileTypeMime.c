//
// Created by masat on 07/11/2019.
//

#include "../headers/extFileTypeMime.h"

static ListFData *initFData();
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo);
static char *getExtFilesPart(const char *allList, const char *mimeType);
static char *getMimeTypesPart(const char *allList, const char *extFile);
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo);

ListFData *fillListFData(const char *nearData, enum FileDataInfo dataInfo) {
    char *allList = NULL;
    ListFData *pListFData = initFData();
    verifyPointer(pListFData, "Problem init FData");

    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "rb");
    verifyPointer(allList, "Problem getContentInFile\n");

    if (strlen(nearData) > 0 && (dataInfo == EXT_FILE || dataInfo == MIME_TYPE)) {
        searchCorrespondingData(pListFData, nearData, allList, dataInfo);
        pListFData->fileDataInfo = dataInfo;
    }

    if (pListFData->numberData <= 0){
        free(pListFData);
        pListFData = NULL;
    }
    free(allList);

    return pListFData;
}

static ListFData *initFData() {

    ListFData *pListFData = malloc(sizeof(ListFData));
    if (pListFData == NULL) {
        return NULL;
    }

    pListFData->data = NULL;
    pListFData->numberData = 0;

    return pListFData;
}

static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo){
    char *concernedPart = NULL;

    concernedPart = (dataInfo == EXT_FILE) ? getExtFilesPart(allList, nearData) : getMimeTypesPart(allList, nearData);

    pListFData->data = strSplit(concernedPart, "|", &pListFData->numberData);

    free(concernedPart);
}

static char *getExtFilesPart(const char *allList, const char *mimeType) {
    char *extFilePart = NULL;
    char *strExtFileType = NULL;
    char *endMimeType = NULL;

    strExtFileType = strstr(allList, mimeType);
    if (strExtFileType == NULL) {
        return NULL;
    }
    while(strExtFileType > allList && *(strExtFileType - 1) != '\n') {
        if (*strExtFileType == ':') {
            endMimeType = strExtFileType;
        }
        strExtFileType -= 1;
    }

    extFilePart = strMallocCpy(strExtFileType, (int)(endMimeType - strExtFileType));

    return extFilePart;
}

static char *getMimeTypesPart(const char *allList, const char *extFile) {
    char *mimeTypePart = NULL;
    char *strMimeType = NULL;
    char *endMimeType = NULL;

    if (strchr(extFile, '/') == NULL) { // check if extension file don't contain '/' that is forbidden in file name
        strMimeType = strstr(allList, extFile);
        if (strMimeType != NULL) {
            strMimeType = strchr(strMimeType, ':') + 1;
            if (strMimeType != NULL) {
                endMimeType = strchr(strMimeType, '\n');
                mimeTypePart = strMallocCpy(strMimeType, (int)(endMimeType - strMimeType));
            }
        }
    }

    return mimeTypePart;
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