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

static char *getLineListExtFileMimeType(const char *mimeType) {
    FILE *fp = NULL;
    char *allList = NULL;
    char *concernedLine = NULL;
    int length = 0;

    allList = getContentInFile(LIST_EXT_FILE_TYPE_MIME, "r");
    // TODO : get correspond line that contain mimeType
    

}

ListFData *searchExtFileByMimeType(const char *mimeType) {
    char *concernedLine = NULL;
    ListFData *pListFData = initFData();
    verifyPointer(pListFData, "Problem init FData");

    concernedLine = getLineListExtFileMimeType(mimeType);

    printf("concernedLine : %s\n", concernedLine);

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