//
// Created by masat on 10/11/2019.
//

#include "../headers/fileNameManager.h"

static char *createAllFilesNames(const char *filesNamesPath);
static char *copyFileNameAndWriteInFile(const char *filesNamesPath, const char *fileName);
static int writeFileNameInListFileNames(const char *filesNamesPath, const char *fileName);

char *getAvailableFileName(const char *dirPath, const char *fileNameNoExt) {
    char *newFileName = NULL;
    char *filesNamesPath = strMallocCat(dirPath, ALL_FILES_NAMES);

    if (access(filesNamesPath, F_OK) != -1) {
        newFileName = createAllFilesNames(filesNamesPath);
    } else {
        newFileName = strMallocCpy("index_sc_0", strlen("index_sc_0"));
        if (newFileName == NULL) {
            return NULL;
        }
        if (writeFileNameInListFileNames(filesNamesPath, newFileName) == 0) {
            free(newFileName);
            free(filesNamesPath);
            return NULL;
        }
    }

    free(filesNamesPath);
    return newFileName;
}

static char *createAllFilesNames(const char *filesNamesPath) {
    FILE *pFilesNames = NULL;;
    char line[100];
    char *newFileName = NULL;
    int number = 0;

    pFilesNames = fopen(filesNamesPath, "rb");
    while(fgets(line, 100, pFilesNames) != NULL) {
    }
    fclose(pFilesNames);

    sscanf(line, "index_sc_%d", &number);
    sprintf(line, "index_sc_%d", ++number);
    newFileName = copyFileNameAndWriteInFile(filesNamesPath, line);

    return newFileName;
}

static char *copyFileNameAndWriteInFile(const char *filesNamesPath, const char *fileName) {
    char *newFileName = strMallocCpy(fileName, (int)strlen(fileName));
    if (newFileName == NULL) {
        fprintf(stderr, "Problem strMallocCpy newFileName in function getAvailableFileName\n");
        return NULL;
    }

    if (writeFileNameInListFileNames(filesNamesPath, newFileName) == 0) {
        free(newFileName);
        return NULL;
    }

    return newFileName;
}

static int writeFileNameInListFileNames(const char *filesNamesPath, const char *fileName) {
    FILE *pFilesNames = NULL;

    pFilesNames = fopen(filesNamesPath, "ab");
    if (pFilesNames == NULL) {
        fprintf(stderr, "Problem open to write file : %s\n", filesNamesPath);
        return 0;
    }
    fprintf(pFilesNames, "%s\n", fileName);
    fclose(pFilesNames);

    return 1;
}