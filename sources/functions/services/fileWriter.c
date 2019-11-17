//
// Created by masat on 17/11/2019.
//

#include "../../headers/services/fileWriter.h"

FILE *startFileWriter(const char *filePath, const char *mode) {
    FILE *fp = NULL;

    if (strcmp(mode, "rb") || strcmp(mode, "r")) {
        fp = fopen(filePath, mode);
        if (fp == NULL) {
            fprintf(stderr, "Problem open file %s\n", filePath);
            return NULL;
        }
        fprintf(fp, "=\n");
    }

    return fp;
}

void closeFileWriter(FILE *fp) {
    fprintf(fp, "\n");
    fclose(fp);
}