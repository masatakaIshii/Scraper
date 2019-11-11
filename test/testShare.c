//
// Created by masat on 11/11/2019.
//

#include "testShare.h"

static FILE *fpError = NULL;

int initManageStderr() {
    fpError = freopen(MANAGE_ERR_FILE, "w", stderr);
    if (fpError == NULL) {
        return -1;
    }
    return 0;
}

int cleanManageStderr() {
    if (0 != fclose(fpError)) {
        return -1;
    }
    fpError = NULL;
    unlink(MANAGE_ERR_FILE);
    return 0;
}

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

int rmrf(char *path) {
    nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
    return rmdir(path);
}