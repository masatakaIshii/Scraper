//
// Created by masat on 17/11/2019.
//

#include "../../headers/services/fileReader.h"

static char *searchAndCopyOptionValue(const char *content, const char *optionName, int *position);

static char **searchAllOptionValues(const char *content, int *count, const char *optionName);

static char **searchOptionValuesOkArrOptionName(const char *content, const char *optionName, int *count);

static char *getProperOptName(const char *content, const char *optionName);
static void removeSpacesAfterOneIndex(char **values, int count);


char *getOptValue(const char *filePath, const char *optionName) {
    char *content = NULL;
    char *result = NULL;

    content = getContentInFile(filePath, "rb");
    if (content == NULL) {
        fprintf(stderr, "ERROR : Problem to get content of file %s in getOptValue\n", filePath);
        return NULL;
    }

    result = searchAndCopyOptionValue(content, optionName, NULL);

    free(content);

    return result;
}

static char *searchAndCopyOptionValue(const char *content, const char *optionName, int *position) {
    char *result = NULL;
    char *startValue = NULL;
    char *endOccur = NULL;

    startValue = getProperOptName(content, optionName);
    if (startValue == NULL) {
        return NULL;
    }
    startValue = strstr(startValue, "->");
    if (startValue == NULL) {
        return NULL;
    }
    startValue += strlen("->");
    while (startValue[0] == ' ') {
        startValue += 1;
    }
    endOccur = strchr(startValue, '}');
    if (position != NULL) {
        *position += (int) (endOccur - content);
    }

    result = strMallocCpy(startValue, (int) (endOccur - startValue));
    if (result == NULL) {
        return NULL;
    }
    return result;
}

char **getAllOptValuesByOptName(const char *filePath, const char *optionName, int *count) {
    char *content = NULL;
    char **result = NULL;

    content = getContentInFile(filePath, "rb");
    if (content == NULL) {
        fprintf(stderr, "ERROR : Problem to get content of file %s in getOptValue\n", filePath);
        return NULL;
    }

    result = searchAllOptionValues(content, count, optionName);

    return result;
}

static char **searchAllOptionValues(const char *content, int *count, const char *optionName) {
    ListStr *pListStr = initListStr(10);
    int position = 0;
    unsigned int contentLength = strlen(content);
    char *optionValue = NULL;
    char *currentPos = (char *) content;

    while (position < contentLength) {
        optionValue = searchAndCopyOptionValue(currentPos, optionName, &position);
        if (optionValue == NULL) {
            break;
        }
        listStrAdd(pListStr, optionValue);
        free(optionValue);
        currentPos += position;
    }

    return destroyListStrAndReturnArrStr(pListStr, count);
}

char **getOptValuesOfArrOptName(const char *filePath, const char *optionName, int *count) {
    char *content = NULL;
    char **result = NULL;

    content = getContentInFile(filePath, "rb");
    if (content == NULL) {
        fprintf(stderr, "ERROR : Problem to get content of file %s in getOptValue\n", filePath);
        return NULL;
    }

    result = searchOptionValuesOkArrOptionName(content, optionName, count);

    return result;
}

static char **searchOptionValuesOkArrOptionName(const char *content, const char *optionName, int *count) {
    ListStr *pListStr = initListStr(10);
    char *optionValue = NULL;
    char *startOpt = NULL;
    char *endOpt = NULL;
    char *startValue = NULL;
    char *endValue = NULL;
    int length = 0;
    int lengthOpt = 0;
    int i = 0;

    startOpt = getProperOptName(content, optionName);
    startOpt = strchr(startOpt, '(') + 1;
    endOpt = strchr(startOpt, ')');

    length = (int) (endOpt - startOpt);

    for (i = 0; i < length; i++) {
        if ((startOpt[i] >= '0' && startOpt[i] <= '9') ||
            (startOpt[i] >= 'a' && startOpt[i] <= 'z') ||
            (startOpt[i] >= 'A' && startOpt[i] <= 'Z')) {
            if (startValue == NULL) {
                startValue = &startOpt[i];
            }
        } else {
            if (startValue != NULL) {
                endValue = &startOpt[i];
                lengthOpt = (int)(endValue - startValue);
                optionValue = strMallocCpy(startValue, lengthOpt);
                listStrAdd(pListStr, optionValue);
                free(optionValue);
                startValue = NULL;
            }
        }
    }

    return destroyListStrAndReturnArrStr(pListStr, count);
}

static char *getProperOptName(const char *content, const char *optionName) {
    char *start = NULL;
    int position = 0;
    int lengthContent = (int) strlen(content);
    int lengthOpt = (int) strlen(optionName);

    while (position < lengthContent) {
        start = strstr(content + position, optionName);
        if (start == NULL) {
            return NULL;
        }
        if (start[-1] == '{' && start[lengthOpt] == ' ' && &start[lengthOpt + 1] == strstr(start, "->")) {
            return start;
        }
        position = (int) (start - content) + lengthOpt;
    }
    return NULL;
}

char **getArrValuesInParenthesis(const char *filePath, const char *delimiter, int *count) {
    char *startPart = NULL;
    char *endPart = NULL;
    char *concernedPart = NULL;
    char *content = NULL;
    char **values = NULL;

    content = getContentInFile(filePath, "rb");
    if (content == NULL) {
        return NULL;
    }

    startPart = strchr(content, '(');
    if (startPart == NULL) {
        return NULL;
    }
    startPart = startPart + 1;

    endPart = strchr(content, ')');
    if (endPart == NULL) {
        return NULL;
    }
    concernedPart = strMallocCpy(startPart, (int)(endPart - startPart));
    values = strSplit(concernedPart, delimiter, count);
    removeSpacesAfterOneIndex(values, *count);

    return values;
}

static void removeSpacesAfterOneIndex(char **values, int count) {
    int i;
    char *temp = NULL;

    for (i = 1; i < count; i++) {
        temp = values[i];
        values[i] = strMallocCpy(temp + 1, strlen(temp) - 1);
        free(temp);
    }
}

//void closeFileReader(FILE *fp) {
//    fclose(fp);
//}