//
// Created by masat on 17/11/2019.
//

#include "../../headers/services/fileWriter.h"

FILE *startFileWriter(const char *filePath, const char *mode) {
    FILE *fp = NULL;

    if (strcmp(mode, "ab") == 0 || strcmp(mode, "a") == 0) {
        fp = fopen(filePath, mode);
        if (fp == NULL) {
            fprintf(stderr, "Problem open file %s\n", filePath);
            return NULL;

        }
        fprintf(fp, "=\n");
    }

    return fp;
}

int writeOptionNameAndValue(FILE *fp, const char *optionName, const char *optionValue) {

    return (fprintf(fp, "{ %s -> %s }\n", optionName, optionValue) >= 0) ? 0 : -1;
}

int writeOptionNameAndArrayValues(FILE *fp, const char *optionName, const char **optionValues, int count) {
    int i;
    int result = 0;

    if (count == 1) {
        result = fprintf(fp, "{ %s -> (%s) }\n", optionName, optionValues[0]);
    } else {
        result = fprintf(fp, "{ %s -> (\n", optionName);
        for (i = 0; i < count && result != -1; i++) {
            result = fprintf(fp, "%s\n", optionValues[i]);
        }
        if (result == -1) {
            return result;
        }
        result = fprintf(fp, ") }\n");
    }

    return (result != -1) ? 0 : result;
}

void closeFileWriter(FILE *fp) {
    fprintf(fp, "\n");
    fclose(fp);
}