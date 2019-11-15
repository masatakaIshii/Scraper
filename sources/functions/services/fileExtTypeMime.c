/*
 *  Filename    : fileExtTypeMime.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to search file extension or mime type in list_file_ext_mime_type.txt and give the appropriate data.
 *                  Check also if the data linked of file extensions / mime type are correct.
 */
#include "../../headers/services/fileExtTypeMime.h"

static ListFData *initFData();
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo);
static char *getExtFilesPart(const char *allList, const char *mimeType);
static char *getMimeTypesPart(const char *allList, const char *fileExt);
static int checkIfFileExtIsInList(const char *allList, const char *fileExt);

/**
 * Fill structure depend to string 'nearData' and the dataInfo :<br>
 * -if dataInfo is FILE_EXT, the structure get extension file depend to mime type in 'nearData'<br>
 * -if dataInfo is MIME_TYPE, tje structure get mime type depend to extension file in 'nearData'
 * @param nearData : string correspond to mime type or extension file
 * @param dataInfo : enum to call the good function:<br>-get file extension<br>-get mime type
 * @return OK pointer of structure ListFData, ERROR NULL
 */
ListFData *fillListFData(const char *nearData, enum FileDataInfo dataInfo) {
    char *allList = NULL;
    ListFData *pListFData = initFData();
    verifyPointer(pListFData, "Problem init FData");

    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "rb");
    verifyPointer(allList, "Problem getContentInFile for function fillListFData\n");

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
 * @return OK pointer of structure ListFData, ERROR NULL
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
 * @param dataInfo : enum to call the good function
 */
static void searchCorrespondingData(ListFData *pListFData, const char *nearData, const char *allList, enum FileDataInfo dataInfo){
    char *concernedPart = NULL;

    concernedPart = (dataInfo == FILE_EXT) ? getExtFilesPart(allList, nearData) : getMimeTypesPart(allList, nearData);

    pListFData->data = strSplit(concernedPart, "|", &pListFData->numberData);

    free(concernedPart);
}

/**
 * Get the file extension depend to the mime type
 * @param allList : string content list of file extension / mime type
 * @param mimeType : the landmark to get file extension(s)
 * @return
 * OK fileExtPart : the line extention part linked to the mime type,<br>
 * ERROR NULL : if the mime type is empty or if its not in file 'listExtFileMimeType.txt'
 */
static char *getExtFilesPart(const char *allList, const char *mimeType) {
    char *fileExtPart = NULL;
    char *strFileExtType = NULL;
    char *endMimeType = NULL;

    strFileExtType = strstr(allList, mimeType);
    if (strFileExtType == NULL) {
        return NULL;
    }
    while(strFileExtType > allList && *(strFileExtType - 1) != '\n') {
        if (*strFileExtType == ':') {
            endMimeType = strFileExtType;
        }
        strFileExtType -= 1;
    }

    fileExtPart = strMallocCpy(strFileExtType, (int)(endMimeType - strFileExtType));

    return fileExtPart;
}

/**
 * Get the mime type part depend to file extention
 * @param allList : string content list of file extension / mime type
 * @param fileExt : the landmark to get mime type(s)
 * @return
 * OK fileExtPart : the line extention part linked to the file extensions,<br>
 * ERROR NULL : if the mime type is empty or if its not in file 'listExtFileMimeType.txt'
 */
static char *getMimeTypesPart(const char *allList, const char *fileExt) {
    char *mimeTypePart = NULL;
    char *strMimeType = NULL;
    char *endMimeType = NULL;

    if (checkIfFileExtIsInList(allList, fileExt)) {

        strMimeType = strstr(allList, fileExt);
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

/**
 * Function to check if the file extension don't contain '/' and is in listFileExtMimeType.txt
 * @param allList
 * @param fileExt
 * @return
 */
static int checkIfFileExtIsInList(const char *allList, const char *fileExt) {
    int indexAfter = 0;

    if (strchr(fileExt, '/') != NULL) { // check if extension file don't contain '/' that is forbidden in file name
        return 0;
    }

    indexAfter = getIndexAfterOccurStr(allList, fileExt);
    if (allList[indexAfter] != '|' && allList[indexAfter] != ':') {
        return 0;
    }
    return 1;
}

/**
 * Function to check if file extension exist in list file extension / mime type
 * @param fileExt : file extension to check
 * @return TRUE 1, FALSE 0
 */
int isFileExtExistsInList(const char *fileExt) {
    int result = 0;
    char *allList = NULL;
    char *mimeTypePart = NULL;
    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "rb");
    if (allList == NULL) {
        fprintf(stderr, "Problem getContentInFile of allList in function isFileExistsInList\n");
        return 0;
    }

    mimeTypePart = getMimeTypesPart(allList, fileExt);
    if (mimeTypePart != NULL) {
        result = 1;
        free(mimeTypePart);
    }

    return result;
}

/**
 * Free pointer of structure ListFData and all of pointer fields
 * @param pListFData : pointer of structure ListFData
 */
void destroyListFData(ListFData *pListFData) {
    int i;
    if (pListFData->numberData > 0) {
        for (i = 0; i < pListFData->numberData; i++) {
            free(pListFData->data[i]);
        }
    }

    free(pListFData);
}