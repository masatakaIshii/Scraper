//
// Created by masat on 16/10/2019.
//

#include "resource.h"

Resource *initResource(const char *url, int depth, int maxDepth) {
    Resource *pResource = NULL;
    if (maxDepth < depth) {
        pResource = malloc(sizeof(Resource));
        if (pResource == NULL) {
            return NULL;
        }
        pResource->depth = depth;
        pResource->maxDepth = maxDepth;
        pResource->pRequest = initRequest(url);
        if (pResource->pRequest == NULL) {
            free(pResource->createdDate);
            free(pResource);
            return NULL;
        }
        pResource->createdDate = NULL;
        pResource->dirResourcePath = NULL;
        pResource->outputPath = NULL;
        pResource->type = NULL;
    }

    return pResource;
}

static int setDirAndOutputPath(Resource *pResource, const char *dirResourcePath) {
    UrlHelper *pUrlHelper = pResource->pRequest->pUrlHelper;
    char *fileNameWithExt = NULL;

    pResource->dirResourcePath = strMallocCpy(dirResourcePath, strlen(dirResourcePath));
    if (pResource->dirResourcePath == NULL) {
        printf("Problem malloc directory path of resource");
        return -1;
    }

    if (pUrlHelper->isExtFile == 1) {
        pResource->outputPath = strMallocCat(pResource->dirResourcePath, pUrlHelper->fileName);
        if (pResource->outputPath == NULL) {
            errorQuit("Problem malloc output file path in resource\n");
            return -1;
        }
    } else {
        if (getExtFileByMimeType(pUrlHelper)) {
            fileNameWithExt = strMallocCat(pUrlHelper->fileName, pUrlHelper->extFile);
            pResource->outputPath = strMallocCat(pResource->dirResourcePath, fileNameWithExt);
        } else {
            return 1;
        }
    }

    return 0;
}

int createFileResource(Resource *pResource, const char *dirResourcePath) {
    int result = setDirAndOutputPath(pResource, dirResourcePath);
    if (result != 0) {

        fprintf(stderr, "Don't found file extention of resource with url '%s'", pResource->pRequest->pUrlHelper->url);
        return -1;
    }

    if (saveRequestInFile(pResource->pRequest, pResource->outputPath) != CURLE_OK) {
        fprintf(stderr, "ERROR request : %s\n", pResource->pRequest->errBuf);
        return -1;
    }

    pResource->createdDate = getCurrentTime();

    return 0;
}

void addResourceInfoInFile(Resource *pResource, const char *resourcesFile) {

}
