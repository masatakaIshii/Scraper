/*
 *  Filename    : fileNameManager.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : Service to manage file names contain in 'all_files_names.txt' to give unique file name if the resource don't have in URL
 */


#include "../../headers/services/fileNameManager.h"

static char *getFileNamesManagerPath(const char *dirPath, const char *manageNameFile);
static char *getNewName(const char *fileNamesManagerPath, const char *nameToAdd, const char *btwNameAndNumber);
static char *createNamesManager(const char *nameWithBtwPart);
static char *addNameInAllFilesNamesManager(const char *fileNamesManagerPath, const char *nameToAdd);
static char *checkNameExistAndGetAvailableOne(const char*contentFileNamesManager, const char *nameToAdd);
static char *getNewNameByNameAndCurrentNbr(const char *nameToAdd, const char *formatName, int number);
static int writeFileNameInListFileNames(const char *filesNamesManagerPath, const char *nameToAdd);
static int checkIfNameIsUsed(const char *fileNamesManagerPath, const char *nameToCheck);

/**
 * Function to get unique name of file depend to file names manager
 * @param fileNamesManager
 * @param dirPath
 * @param nameToAdd
 * @param btwNameAndNumber
 * @return OK newName : new available name
 * ERROR NULL
 */
char *getAvailableName(const char *fileNamesManager, const char *dirPath, const char *nameToAdd, const char *btwNameAndNumber) {
    char *newName = NULL; // new name deliver by file names manager
    char *fileNamesManagerPath = NULL;

    if (fileNamesManager == NULL || strlen(fileNamesManager) <= 0) {
        fprintf(stderr, "ERROR in getAvailableName : the fileNamesManager can\'t be empty\n");
        return NULL;
    }

    fileNamesManagerPath = getFileNamesManagerPath(dirPath, fileNamesManager);

    newName = getNewName(fileNamesManagerPath, nameToAdd, btwNameAndNumber);

    free(fileNamesManagerPath);
    return newName;
}

/**
 * Get the file names manager path
 * @param dirPath : directory path that contain file names manager
 * @param manageNameFile
 * @return
 */
static char *getFileNamesManagerPath(const char *dirPath, const char *manageNameFile) {
    char *temp = NULL; // temp address of char to add '/'
    char *fileNamesManagerPath = NULL;

    if (strlen(dirPath) > 0) {
        mkdirP(dirPath);
        temp = strMallocCat(dirPath, "/");
        fileNamesManagerPath = strMallocCat(temp, manageNameFile);
        free(temp);
        if (fileNamesManagerPath == NULL) {
            return NULL;
        }
    } else {
        fileNamesManagerPath = strMallocCpy(manageNameFile, (int)strlen(manageNameFile));
        if (fileNamesManagerPath == NULL) {
            return NULL;
        }
    }

    return fileNamesManagerPath;
}

/**
 * Get new name and add the name in file names manager
 * @param fileNamesManagerPath : the file path that contain names that is used
 * @param nameToAdd : the name to add in file names manager
 * @param btwNameAndNumber : the separator between name and number
 * @return OK newName : the name that is unique in context of file names manager
 * ERROR NULL
 */
static char *getNewName(const char *fileNamesManagerPath, const char *nameToAdd, const char *btwNameAndNumber) {
    char *newName = NULL; // new name deliver by file names manager
    char *nameWithBtwPart = NULL; // concat nameToAdd and btwNameAndNumber

    nameWithBtwPart = strMallocCat(nameToAdd, btwNameAndNumber);

    if (access(fileNamesManagerPath, F_OK) == -1) {
        newName = createNamesManager(nameWithBtwPart);
    } else {
        newName = addNameInAllFilesNamesManager(fileNamesManagerPath, nameWithBtwPart);
    }
    free(nameWithBtwPart);
    if (newName == NULL) {
        return NULL;
    }
    if (!writeFileNameInListFileNames(fileNamesManagerPath, newName)) {
        free(newName);
        return NULL;
    }

    return newName;
}

/**
 * Function to create file 'all_files_names.txt', add new file name in the file and return new file name
 * @param filesNamesPath : the path to create new 'all_files_names.txt'
 * @return newName : the new unique file name with like 'index_sc_n' where n is number
 */
static char *createNamesManager(const char *nameWithBtwPart) {
    char *newName = NULL; // new name deliver by file names manager

    newName = strMallocCat(nameWithBtwPart, "0");
    if (newName == NULL) {
        fprintf(stderr, "ERROR in fileNameManager : Problem strMallocCat newName in createNamesManager\n");
    }

    return newName;
}

/**
 *
 * @param fileNamesManagerPath
 * @param nameToAdd
 * @return
 */
static char *addNameInAllFilesNamesManager(const char *fileNamesManagerPath, const char *nameToAdd) {
    char *contentFilesNamesManager = NULL; // content of file names manager
    char *newName = NULL; // new name deliver by file names manager

    contentFilesNamesManager = getContentInFile(fileNamesManagerPath, "rb");
    if (contentFilesNamesManager == NULL) {
        fprintf(stderr, "ERROR : Problem to open file to read in : %s\n", fileNamesManagerPath);
        return NULL;
    }

    newName = checkNameExistAndGetAvailableOne(contentFilesNamesManager, nameToAdd);
    free(contentFilesNamesManager);

    return newName;
}

/**
 * Check the content of file names manager and give available name
 * @param contentFileNamesManager : the content of file names manager
 * @param nameToAdd : name without number to check occurence and concat with appropriate number
 * @return OK newName : the available name that is add in end of file names manager
 * ERROR : NULL;
 */
static char *checkNameExistAndGetAvailableOne(const char*contentFileNamesManager, const char *nameToAdd) {
    char *newName = NULL; // new available name deliver by file names manager
    char *lineOccurStr = NULL; // line that have occurrence of nameToAdd
    char *formatName = NULL; // format with nameToAdd to add number
    char *lastOccur = myStrrstr(contentFileNamesManager, nameToAdd); // begin of last occurence of nameToAdd
    int indexAtLineBreak = 0; // index of '\n'
    int currentNbr = -1; // if occurrence, current number to nameToAdd in file names manager

    formatName  = strMallocCat(nameToAdd, "%d");
    if (formatName == NULL) {
        return NULL;
    }
    if (lastOccur != NULL) {
        indexAtLineBreak = getIndexAfterOccurStr(lastOccur, "\n");
        lineOccurStr = strMallocCpy(lastOccur, indexAtLineBreak - 1);
        if (lineOccurStr == NULL) {
            return NULL;
        }
        sscanf(lineOccurStr, formatName, &currentNbr);
    } else {
        currentNbr = -1;
    }
    newName = getNewNameByNameAndCurrentNbr(nameToAdd, formatName, ++currentNbr);
    free(lineOccurStr);
    free(formatName);

    return newName;
}

/**
 * Get the name that is n + 1 of current name
 * @param nameToAdd : name that content number count in name
 * @param formatName : format to change the last occurrence name to n + 1
 * @param number : current number contain in name to increment
 * @return OK newName : new unique name to add in file Names manager, <br>
 * ERROR NULL
 */
static char *getNewNameByNameAndCurrentNbr(const char *nameToAdd, const char *formatName, int number) {
    char *newName = NULL; // new available name deliver by file names manager
    int digitLength = getNbrDigit(number); // length of number if it'll be string

    newName = calloc(strlen(nameToAdd) + digitLength + 1, sizeof(char));
    if (newName == NULL) {
        return NULL;
    }

    sprintf(newName, formatName, number);

    return newName;
}

/**
 * Function to add name to the file of name manager
 * @param filesNamesManagerPath : the path of file 'all_files_names.txt'
 * @param nameToAdd : the name to add in file
 * @return OK 1, ERROR 0
 */
static int writeFileNameInListFileNames(const char *filesNamesManagerPath, const char *nameToAdd) {
    FILE *pFilesNames = NULL;

    pFilesNames = fopen(filesNamesManagerPath, "ab");
    if (pFilesNames == NULL) {
        fprintf(stderr, "Problem open to write file : %s\n", filesNamesManagerPath);
        return 0;
    }
    fprintf(pFilesNames, "%s\n", nameToAdd);
    fclose(pFilesNames);

    return 1;
}

/**
 * Function to add name in file names manager if its not include
 * @param dirPath : directory path that have file names manager
 * @param filesNamesManager : the name of file names manager
 * @param nameToCheck : the name to check if its in file names manager
 * @return OK 1 : the name is add in file name manager
 * ERROR 0 : the name is not add because it's exist alreay
 */
int addNameIfNotInFilesNamesManager(const char *dirPath, const char *filesNamesManager, const char *nameToCheck) {
    char *fileNamesPath = NULL;

    mkdirP(dirPath);
    fileNamesPath = getFileNamesManagerPath(dirPath, filesNamesManager);

    if (access(fileNamesPath, F_OK) != -1) {
        if (checkIfNameIsUsed(fileNamesPath, nameToCheck)) {
            return 0;
        }
    }
    writeFileNameInListFileNames(fileNamesPath, nameToCheck);

    return 1;
}

/**
 * Function to check if name in file names manager is already used
 * @param fileNamesManagerPath : path that contain all names used by file names manager
 * @param nameToCheck : name to check
 * @return OK 1 : name is add in file names manager
 * OK 0 : name is already in file names manager
 * ERROR -1 : problem to get content of file name manager
 */
static int checkIfNameIsUsed(const char *fileNamesManagerPath, const char *nameToCheck) {
    char *contentFile = NULL;
    int result = 0;

    contentFile = getContentInFile(fileNamesManagerPath, "rb");
    if (contentFile == NULL) {
        fprintf(stderr, "ERROR : Problem to get content of file %s\n", fileNamesManagerPath);
        return -1;
    }

    result = (strstr(contentFile, nameToCheck) != NULL) ? 1 : 0;

    free(contentFile);

    return result;
}

/**

 */

/**
 * Delete file name manager by given directory path and the name of file
 * @param dirPath
 * @param fileNamesManager
 * @return OK 1, ERROR 0
 */
int deleteFilesNamesManager(const char *dirPath, const char *fileNamesManager) {
    int result = 0;
    char *allFilesNamesPath = strMallocCat(dirPath, fileNamesManager);

    result = unlink(allFilesNamesPath);
    free(allFilesNamesPath);

    return result == 0;
}