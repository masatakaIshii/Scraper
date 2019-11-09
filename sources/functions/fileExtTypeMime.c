//
// Created by masat on 07/11/2019.
//

#include "../headers/extFileTypeMime.h"

static ListFData *initFData();
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo);
static char *getExtFilesPart(const char *allList, const char *mimeType);
static char *getMimeTypesPart(const char *allList, const char *extFile);

/**
 * fill structure depend to string 'nearData' and the dataInfo :<br>
 * -if dataInfo is FILE_EXT, the structure get extension file depend to mime type in 'nearData'<br>
 * -if dataInfo is MIME_TYPE, tje strictire get mime type depend to extension file in 'nearData'
 * @param nearData : string correspond to mime type or extension file
 * @param dataInfo : enum to call the good function:<br>-get file extension<br>-get mime type
 * @return pointer of structure ListFData.
 */
ListFData *fillListFData(const char *nearData, enum FileDataInfo dataInfo) {
    char *allList = NULL;
    ListFData *pListFData = initFData();
    verifyPointer(pListFData, "Problem init FData");

    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "rb");
    verifyPointer(allList, "Problem getContentInFile\n");

    if (strlen(nearData) > 0 && (dataInfo == FILE_EXT || dataInfo == MIME_TYPE)) {
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

/**
 * Function to init structure ListFData
 * @return pointer of structure ListFData
 */
static ListFData *initFData() {

    ListFData *pListFData = malloc(sizeof(ListFData));
    if (pListFData == NULL) {
        return NULL;
    }

    pListFData->data = NULL;
    pListFData->numberData = 0;

    return pListFData;
}

/**
 * Function to call appropriate function depend to dataInfo :<br>
 * -get extension file by mime type<br>
 * -get mime type by extension file
 * @param pListFData : pointer of structure ListFData
 * @param nearData : string correspond to landmark to get info and fill structure pListFData
 * @param allList : string contains list of file extension / mime type
 * @param dataInfo : enum to call the good function:<br>-get file extension<br>-get mime type
 */
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo){
    char *concernedPart = NULL;

    concernedPart = (dataInfo == FILE_EXT) ? getExtFilesPart(allList, nearData) : getMimeTypesPart(allList, nearData);

    pListFData->data = strSplit(concernedPart, "|", &pListFData->numberData);

    free(concernedPart);
}

/**
 * get the file extension depend to the mime type
 * @param allList :
 * @param mimeType
 * @return
 */
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