//
// Created by masat on 11/11/2019.
//

#ifndef SCRAPER_TESTSHARE_H
#define SCRAPER_TESTSHARE_H

#include <stdio.h>
#include <ftw.h>

#define MANAGE_ERR_FILE "errors.txt"

int initManageStderr();

int cleanManageStderr();

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int rmrf(char *path);

#endif //SCRAPER_TESTSHARE_H
