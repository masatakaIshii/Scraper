/*
 *  Filename    : fileNameManager.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to manage file names contain in 'all_files_names.txt' to give unique file name if the resource don't have in URL
 */


#include "../../headers/services/fileNameManager.h"

static char *getFilesNamesPath(const char *dirPath, const char *manageNameFile);
static char *getNewFileName(const char *filesNamesPath, const char *nameToAdd, const char *btwNameAndNumber);
static char *createAllFilesNames( const char *nameWithBtwPart);
static char *addFileNameInAllFilesNames(const char *filesNamesPath, const char *nameToAdd);
static char *checkFileNameExistAndGetAvailableOne(const char*contentAllFilesNames, const char *nameToAdd);
static char *getNewNameByNameAndCurrentNbr(const char *nameToAdd, const char *formatName, int number);
static int writeFileNameInListFileNames(const char *filesNamesPath, const char *nameToAdd);

/**
 * Function to get unique name for resource that not have file name in URL
 * TODO: complete documentation after it's done
 */
char *getAvailableFileName(const char *manageNameFile, const char *dirPath, const char *nameToAdd, const char *btwNameAndNumber) {
    char *newFileName = NULL;
    char *filesNamesPath = NULL;

    if (manageNameFile == NULL || strlen(manageNameFile) <= 0) {
        fprintf(stderr, "ERROR in getAvailableFileName : the manageNameFile can\'t be empty\n");
        return NULL;
    }

    filesNamesPath = getFilesNamesPath(dirPath, manageNameFile);

    newFileName = getNewFileName(filesNamesPath, nameToAdd, btwNameAndNumber);

    free(filesNamesPath);
    return newFileName;
}

static char *getFilesNamesPath(const char *dirPath, const char *manageNameFile) {
    char *temp = NULL;
    char *filesNamesPath = NULL;

    if (strlen(dirPath) > 0) {
        mkdirP(dirPath);
        temp = strMallocCat(dirPath, "/");
        filesNamesPath = strMallocCat(temp, manageNameFile);
        free(temp);
        if (filesNamesPath == NULL) {
            return NULL;
        }
    } else {
        filesNamesPath = strMallocCpy(manageNameFile, (int)strlen(manageNameFile));
        if (filesNamesPath == NULL) {
            return NULL;
        }
    }

    return filesNamesPath;
}

static char *getNewFileName(const char *filesNamesPath, const char *nameToAdd, const char *btwNameAndNumber) {
    char *newFileName = NULL;
    char *nameWithBtwPart = NULL;

    nameWithBtwPart = strMallocCat(nameToAdd, btwNameAndNumber);

    if (access(filesNamesPath, F_OK) == -1) {
        newFileName = createAllFilesNames(nameWithBtwPart);
    } else {
        newFileName = addFileNameInAllFilesNames(filesNamesPath, nameWithBtwPart);
    }
    free(nameWithBtwPart);
    if (newFileName == NULL) {
        return NULL;
    }
    if (!writeFileNameInListFileNames(filesNamesPath, newFileName)) {
        free(newFileName);
        return NULL;
    }

    return newFileName;
}

/**
 * Function to create file 'all_files_names.txt', add new file name in the file and return new file name
 * @param filesNamesPath : the path to create new 'all_files_names.txt'
 * @return newFileName : the new unique file name with like 'index_sc_n' where n is number
 */
static char *createAllFilesNames( const char *nameWithBtwPart) {
    char *newFileName = NULL;

    newFileName = strMallocCat(nameWithBtwPart, "0");
    if (newFileName == NULL) {
        fprintf(stderr, "ERROR in fileNameManager : Problem strMallocCat newFileName in createAllFilesNames\n");
    }

    return newFileName;
}

static char *addFileNameInAllFilesNames(const char *filesNamesPath, const char *nameToAdd) {
    char *contentAllFilesNames = NULL;;
    char *newFileName = NULL;

    contentAllFilesNames = getContentInFile(filesNamesPath, "rb");
    if (contentAllFilesNames == NULL) {
        fprintf(stderr, "Problem to open file to read in : %s\n", filesNamesPath);
        return NULL;
    }

    newFileName = checkFileNameExistAndGetAvailableOne(contentAllFilesNames, nameToAdd);
    free(contentAllFilesNames);

    return newFileName;
}

static char *checkFileNameExistAndGetAvailableOne(const char*contentAllFilesNames, const char *nameToAdd) {
    char *newFileName = NULL;
    char *lineOccurStr = NULL;
    char *lastOccur = myStrrstr(contentAllFilesNames, nameToAdd);
    char *formatName = strMallocCat(nameToAdd, "%d");
    int indexAtLineBreak = 0;
    int currentNbr = -1;

    if (lastOccur != NULL) {
        indexAtLineBreak = getIndexAfterOccurStr(lastOccur, "\n");
    }

    lineOccurStr = strMallocCpy(lastOccur, indexAtLineBreak - 1);
    if (lineOccurStr == NULL) {
        return NULL;
    }
    sscanf(lineOccurStr, formatName, &currentNbr);
    newFileName = getNewNameByNameAndCurrentNbr(nameToAdd, formatName, ++currentNbr);

    free(lineOccurStr);
    free(formatName);

    return newFileName;
}

static char *getNewNameByNameAndCurrentNbr(const char *nameToAdd, const char *formatName, int number) {
    char *newName = NULL;
    int digitLength = getNbrDigit(number);

    newName = calloc(strlen(nameToAdd) + digitLength + 1, sizeof(char));
    if (newName == NULL) {
        return NULL;
    }

    sprintf(newName, formatName, number);

    return newName;
}

/**
 * Function to add name to the file 'all_files_names.txt'
 * @param filesNamesPath : the path of file 'all_files_names.txt'
 * @param nameToAdd : the name to add in file
 * @return OK 1, ERROR 0
 */
static int writeFileNameInListFileNames(const char *filesNamesPath, const char *nameToAdd) {
    FILE *pFilesNames = NULL;

    pFilesNames = fopen(filesNamesPath, "ab");
    if (pFilesNames == NULL) {
        fprintf(stderr, "Problem open to write file : %s\n", filesNamesPath);
        return 0;
    }
    fprintf(pFilesNames, "%s\n", nameToAdd);
    fclose(pFilesNames);

    return 1;
}

/**
 * Delete 'all_files_names.txt' by given the directory path that is contain
 * @param dirPath
 * @return OK 1, ERROR 0
 */
int deleteAllFilesNamesFiles(const char *dirPath) {
    int result = 0;
    char *allFilesNamesPath = strMallocCat(dirPath, ALL_FILES_NAMES);
    result = unlink(allFilesNamesPath);
    free(allFilesNamesPath);

    return result == 0;
}