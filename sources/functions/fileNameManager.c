//
// Created by masat on 10/11/2019.
//

#include "../headers/fileNameManager.h"

static char *createAllFilesNames(const char *filesNamesPath);
static char *copyFileNameAndWriteInFile(const char *filesNamesPath, const char *fileName);
static int writeFileNameInListFileNames(const char *filesNamesPath, const char *fileName);

/**
 * Function to get unique name for resource that not have file name in URL
 * DEBT : fileNameNoExt is for manage the case when 2 different url have the same file name, now it is not manage
 * @param dirPath : the directory path
 * @param fileNameNoExt : the file to add "_sc_n" where 'n' is number that is available
 * @return OK newFileName : unique file name,
 * ERROR NULL
 */
char *getAvailableFileName(const char *dirPath, const char *fileNameNoExt) {
    char *newFileName = NULL;
    char *filesNamesPath = strMallocCat(dirPath, ALL_FILES_NAMES);

    if (access(filesNamesPath, F_OK) != -1) {
        newFileName = createAllFilesNames(filesNamesPath);
    } else {
        newFileName = copyFileNameAndWriteInFile(filesNamesPath, "index_sc_0");
    }

    free(filesNamesPath);
    return newFileName;
}

/**
 * Function to create file 'all_files_names.txt', add new file name in the file and return new file name
 * @param filesNamesPath : the path to create new 'all_files_names.txt'
 * @return newFileName : the new unique file name with like 'index_sc_n' where n is number
 */
static char *createAllFilesNames(const char *filesNamesPath) {
    FILE *pFilesNames = NULL;;
    char line[100];
    char *newFileName = NULL;
    int number = 0;

    pFilesNames = fopen(filesNamesPath, "rb");
    if (pFilesNames == NULL) {
       fprintf(stderr, "Problem to open file to read in : %s\n", filesNamesPath);
       return NULL;
    }
    while(fgets(line, 100, pFilesNames) != NULL) {
    }
    fclose(pFilesNames);

    sscanf(line, "index_sc_%d", &number);
    sprintf(line, "index_sc_%d", ++number);
    newFileName = copyFileNameAndWriteInFile(filesNamesPath, line);

    return newFileName;
}

/**
 * Function to copy new file name to array of char that is malloc and add in all_files_names.txt
 * @param filesNamesPath : the path of all_files_names.txt
 * @param fileName : the file name to malloc
 * @return OK newFileName : the file name that is malloc, ERROR NULL
 */
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

/**
 * Function to add name to the file 'all_files_names.txt'
 * @param filesNamesPath : the path of file 'all_files_names.txt'
 * @param fileName : the name to add in file
 * @return OK 1, ERROR 0
 */
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