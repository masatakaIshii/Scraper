/*
 *  Filename    : common.c
 *
 *  Made by     : Masataka ISHII
 *
 *  Description : common functions for application
 */
#include "../headers/common.h"

/**
 * Verify the pointer and if its null, show message and quit program with exit status '1'
 * @param pointer
 * @param message
 */
void verifyPointer(void *pointer, const char *message) {
    if (pointer == NULL) {
        destroyApp();
        fprintf(stderr, "%s", message);
        curl_global_cleanup();
        exit(1);
    }
}

/**
 * Get number of digit of param number
 * @param number : integer to see the number of digit
 * @return OK count > 0
 * ERROR 0 : when number is less than 0
 */
int getNbrDigit(int number) {
    int count = 0;

    if (number < 0) {
        return 0;
    }

    if (number == 0) {
        return 1;
    }

    while (number > 0) {
        number /= 10;
        count++;
    }
    return count;
}

/**
 * Strcat with proper malloc and not static array of character
 * @param str1
 * @param str2
 * @return OK newStr : string that is concat with str1 and str2, <br>
 * ERROR NULL : problem calloc of newStr
 */
char *strMallocCat(const char *str1, const char *str2) {
    char *newStr = NULL;
    int length1 = (str1 != NULL) ? (int) strlen(str1) : 0;
    int length2 = (str2 != NULL) ? (int) strlen(str2) : 0;

    newStr = calloc(length1 + length2 + 1, sizeof(char));
    if (newStr == NULL) {
        return NULL;
    }

    if (str1 != NULL) {
        strcpy(newStr, str1);
    } else {
        strcpy(newStr, "");
    }
    if (str2 != NULL) {
        strcat(newStr, str2);
    }

    return newStr;
}

/**
 * Function to realloc currentStr with string to add and concat
 * @param currentStr : current string to realloc
 * @param strToAdd : string to add in current string
 * @return OK currentStr : currentString with string that is add, <br>
 * ERROR NULL
 */
char *strReallocCat(char *currentStr, const char *strToAdd) {
    int lengthCurrentStr = (currentStr != NULL) ? (int) strlen(currentStr) : 0;
    int lengthStrToAdd = (strToAdd != NULL) ? (int) strlen(strToAdd) : 0;

    currentStr = realloc(currentStr, lengthCurrentStr + lengthStrToAdd + 1);
    if (currentStr == NULL) {
        return NULL;
    }
    if (lengthCurrentStr == 0) {
        memset(currentStr, 0, lengthCurrentStr + lengthStrToAdd + 1);
    }
    if (strToAdd != NULL) {
        strcat(currentStr, strToAdd);
    }

    return currentStr;
}

/**
 * Malloc and copy string with precise length
 * @param str
 * @param length
 * @return newStr : new string that is malloc
 */
char *strMallocCpy(const char *str, int length) {
    char *newStr = calloc(length + 1, sizeof(char));
    if (newStr == NULL) {
        return NULL;
    }

    strncpy(newStr, str, length);
    return newStr;
}

/**
 * Function to get the number of occurence in string
 * @param str : string to view of there are occurence
 * @param occur : occur
 * @return result : number of occurence in string 'str'
 */
int getNbrOccurInStr(const char *str, const char *occur) {
    char *temp = NULL;
    int result = 0;

    temp = strstr(str, occur);
    while (temp != NULL) {
        result++;
        if (strstr(temp, occur) != NULL) {
            temp = strstr(temp + 1, occur);
        }
    }
    return result;
}

/**
 * Function to get last occurrence of string
 * @param string : string to search the occurence
 * @param lastOccur : occurence to return if it's in string
 * @return OK address of char that occurrence start, <br>
 * ERROR NULL
 */
char *myStrrstr(const char *string, const char *lastOccur) {
    int index = (int) strlen(string) - 1;
    int lengthOccur = (int) strlen(lastOccur);

    while (index >= lengthOccur - 1) {
        if (string[index] == lastOccur[lengthOccur - 1]) {
            if (strncmp(&string[index] - (lengthOccur - 1), lastOccur, lengthOccur) == 0) {
                return (char *) &string[index] - (lengthOccur - 1);
            }
        }
        index--;
    }

    return NULL;
}

/**
 * Extract content string to few token that split by delimiter
 * @param count : number of delimiter
 * @param temp : string to split
 * @param delimiter : delimiter that split temp string
 * @return OK array of string that is split by delimiter, <br>
 * ERROR NULL
 */
static char **extractTokAndSaveInResult(int count, char *temp, const char *delimiter) {
    int i = 0;
    char *token = NULL;
    char **result = malloc(sizeof(char *) * count);
    if (result == NULL) {
        fprintf(stderr, "ERROR in extractTokAndSaveInResult : Problem malloc of result\n");
        return NULL;
    }

    token = strtok(temp, delimiter);
    while (token != NULL) {
        if (strlen(token) > 0) {
            result[i] = strMallocCpy(token, (int) strlen(token));
            if (result[i] == NULL) {
                freeArrayString(result, i);
                free(result);
                fprintf(stderr, "ERROR in extractTokAndSaveInResult : Problem strMallocCpy the token to result[%d]", i);
                return NULL;
            }
            i++;
        }
        token = strtok(NULL, delimiter);
    }

    return result;
}

/**
 * Function to operate split of string to array of string by delimiter
 * @param str
 * @param delimiter
 * @param count
 * @return result : array of string
 */
static char **fillArraySplitStr(const char *str, const char *delimiter, int count) {
    char *temp; // string to malloc, to use strtok without affect param str
    char **result;// = malloc(sizeof(char *) * count);

    temp = strMallocCpy(str, (int) strlen(str));
    if (temp == NULL) {
        fprintf(stderr, "ERROR in fillArraySplitStr : Problem strMallocCpy temp in fillArraySplitStr\n");
        return NULL;
    }

    result = extractTokAndSaveInResult(count, temp, delimiter);
    if (result == NULL) {
        free(temp);
        fprintf(stderr, "ERROR in fillArraySplitStr : Problem strMallocCpy temp in fillArraySplitStr\n");
        return NULL;
    }

    free(temp);

    return result;
}

/**
 * Function to split string to array of string by delimitor
 * @param str : string to copy to split in array
 * @param pCount : count of array string
 * @return
 * OK arrayStr : array of string, <br>
 * ERROR NULL : if str is empty
 */
char **strSplit(const char *str, const char *delimiter, int *pCount) {
    char **arrayStr = NULL;

    if (str == NULL || delimiter == NULL || strlen(str) == 0 || strlen(delimiter) == 0) {
        return NULL;
    }
    *pCount = getNbrOccurInStr(str, delimiter) + 1;

    arrayStr = fillArraySplitStr(str, delimiter, *pCount); // operate split of string 'str'

    return arrayStr;
}

/**
 * Function to properStrSplit
 * @param content
 * @param delimiter
 * @param count
 * @return
 */
char **properStrSplit(const char *content, const char *delimiter, int *count) {
    char **arrStr = NULL;
    char *lastOccur = myStrrstr(content, delimiter);
    char *startOccur = strstr(content, delimiter);
    int length = 0;

    arrStr = strSplit(content, delimiter, count);
    length = (int)(lastOccur - content);

    if (length + strlen(delimiter) == strlen(content)) {
        (*count)--;
        if (lastOccur != startOccur && strncmp(content, delimiter, strlen(delimiter)) == 0) {
            (*count)--;
        }
    }

    return arrStr;
}

/**
 * Free array of string
 * @param arrayStr : array of string to free
 * @param count : number of string in arrayStr
 */
void freeArrayString(char **arrayStr, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        free(arrayStr[i]);
    }

    free(arrayStr);
}

/**
 * Get index of array of char strCheck after the occurrence of string strOccur
 * @param strCheck : string to search if there are occurrence
 * @param strOccur : string correspond to occurrence
 * @return index : index after occurrence strOccur
 */
int getIndexAfterOccurStr(const char *strCheck, const char *strOccur) {
    char *startOccur = NULL;

    if (strCheck != NULL && strOccur != NULL) {
        startOccur = strstr(strCheck, strOccur);

        if (startOccur != NULL) {
            return (int) (startOccur - strCheck + strlen(strOccur));
        }
    }

    return 0;
}

/**
 * Function to write content and manage line break depend to OS
 * @param fp
 * @param lengthFile
 * @return : string that correspond to content of file
 */
static char *writeContentOfFile(FILE *fp, int lengthFile) {
    char checkChar;
    char *result = NULL;
    int i = 0;

    result = calloc(lengthFile + 1, sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Problem with calloc to get content file in common.c\n");
        fclose(fp);
        return NULL;
    }

    while (fread(&checkChar, sizeof(char), 1, fp), !feof(fp)) {
        // TODO : manage depend to OS
        if (checkChar != '\r') {
            result[i] = checkChar;
            i++;
        }
    }

    return result;
}

/**
 * Get content of file content in filePath
 * @param filePath
 * @param mode : can be 'r' or 'rb'
 * @return
 */
char *getContentInFile(const char *filePath, const char *mode) {
    int length = 0;
    char *result = NULL;
    FILE *fp;
    if (strcmp("r", mode) != 0 && strcmp("rb", mode) != 0) {
        return NULL;
    }
    fp = fopen(filePath, mode);
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    rewind(fp);
    result = writeContentOfFile(fp, length);

    fclose(fp);

    return result;
}

unsigned long getCurrentTimeSec() {
    time_t currentTime;
    currentTime = time(NULL);
    if (currentTime == (time_t) -1) {
        fprintf(stderr, "Problem to set time in getCurrentTime\n");
        return -1;
    }
    return (unsigned long)currentTime;
}

char *getTimeToString(unsigned long seconds) {
    time_t currentTime;
    char *strCurrentTime = NULL;
    char *temp = NULL;

    currentTime = seconds;

    temp = ctime(&currentTime);
    strCurrentTime = strMallocCpy(temp, (int) strlen(temp));
    if (strCurrentTime == NULL) {
        fprintf(stderr, "Problem get current time\n");
        return NULL;
    }

    return strCurrentTime;
}

/**
 * Get current time format "strDate strMonth intDate intHours:intMin:intSec intYears"
 * Example : "Sun Oct 01 13:12:00 2019"
 * @return string content current time
 */
char *getCurrentTime() {
    time_t currentTime;
    char *strCurrentTime = NULL;
    char *temp = NULL;

    currentTime = time(NULL);
    if (currentTime == (time_t) -1) {
        fprintf(stderr, "Problem to set time in getCurrentTime\n");
        return NULL;
    }

    temp = ctime(&currentTime);
    strCurrentTime = strMallocCpy(temp, (int) strlen(temp));
    if (strCurrentTime == NULL) {
        fprintf(stderr, "Problem get current time\n");
        return NULL;
    }

    return strCurrentTime;
}

static unsigned long getAllTimesValuesToSec(int years, int hours, int minutes, int seconds) {
    unsigned long result = seconds;
    result += 60 * minutes;
    result += 3600 * hours;
    result += 31536000 * (years - 1970);
    return result;
}

/**
 * Destroy pointer if boolean of field is == 1, and affect boolean to 0
 * @param pointer : the pointer to free
 * @param isMalloc : variable of boolean to check if pointer is already malloc and put to 0
 */
void freePointer(void **pointer, short *isMalloc) {
    if (*isMalloc == 1) {
        free(*pointer);
        *pointer = NULL;
        *isMalloc = 0;
    }
}

/**
 * Check if directory path is correct
 * DEBT : the backslash is include in forbidden chars because the function below depend to mkdirP
 * @param dirPath
 * @return
 * 1 : dirPath is correct
 * 0 : dirPath contain forbidden Chars
 */
static int checkIfDirPathIsCorrect(const char *dirPath) {
    char *arrayForbiddenChars = "\\<>?\":*|";

    return strpbrk(dirPath, arrayForbiddenChars) == NULL;
}

/**
 * Function to create directories step by step thanks to token
 * @param dirPath
 * @return
 * 0 : operation success
 * -1 : problem with token
 */
static int createDirectories(const char *dirPath) {
    const char s[2] = "/";
    unsigned length = strlen(dirPath);
    char temp[length];
    char currentDirPath[length];
    char *token;

    strcpy(temp, dirPath);
    token = strtok(temp, s);
    if (token == NULL) {
        return -1;
    }

    strcpy(currentDirPath, token);
    while (token != NULL) {
        mkdir(currentDirPath);
        token = strtok(NULL, s);
        if (token != NULL) {
            strcat(currentDirPath, "/");
            strcat(currentDirPath, token);
        }
    }
    return 0;
}

/**
 * Function to create directories recursively like mkdirP
 * @param dirPath
 * @return
 * 0 : correct value and directories created
 * -1 : error value, because of directory path wrong value
 */
int mkdirP(const char *dirPath) {

    if (checkIfDirPathIsCorrect(dirPath) == 0) {
        return -1;
    }

    return createDirectories(dirPath);
}

/**
 * Function to verify if the directory exist
 * @param dirPath
 * @return
 * 1 : directory that have dirPath value exist
 * 0 : directory that is dirPath not exist
 */
int checkIfDirExist(char *dirPath) {
    DIR *dir = opendir(dirPath);
    if (dir) {
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        return 0;
    } else {
        fprintf(stderr, "Problem to open dir : %s\n", dirPath);
        return 0;
    }
}