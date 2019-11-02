//
// Created by masat on 16/10/2019.
//

#include "resource.h"

static void initFieldsResource(Resource *pResource, int depth, int maxDepth) {
    pResource->depth = depth;
    pResource->maxDepth = maxDepth;

    pResource->isCreatedDate = 0;
    pResource->createdDate = NULL;

    pResource->isDirResourcePath = 0;
    pResource->dirResourcePath = NULL;

    pResource->isOutputPath = 0;
    pResource->outputPath = NULL;

    pResource->isType = 0;
    pResource->type = NULL;

    pResource->isRequest = 0;
}

Resource *initResource(const char *url, int depth, int maxDepth) {
    Resource *pResource = NULL;
    if (maxDepth >= 0 && depth >= 0 && maxDepth >= depth) {
        pResource = malloc(sizeof(Resource));
        if (pResource == NULL) {
            return NULL;
        }
        initFieldsResource(pResource, depth, maxDepth);
        pResource->pRequest = initRequest(url);
        if (pResource->pRequest == NULL) {
            free(pResource);
            return NULL;
        }
        pResource->isRequest = 1;
    }

    return pResource;
}

static int setOutputPath(Resource *pResource) {
    UrlHelper *pUrlHelper = pResource->pRequest->pUrlHelper;
    char *fileNameWithExt = NULL;

    if (pUrlHelper->isExtFile == 1) {
        pResource->outputPath = strMallocCat(pResource->dirResourcePath, pUrlHelper->fileName);
        verifyPointer(pResource->outputPath, "Problem malloc output file path in resource\n");
    } else {
        if (getExtFileByMimeType(pUrlHelper)) { // fetch extension file by mime type search in conditions and list extFile / mimeType
            fileNameWithExt = strMallocCat(pUrlHelper->fileName, pUrlHelper->extFile);
            verifyPointer(fileNameWithExt, "Problem malloc string fileNameWithExt path in resource\n");

            pResource->outputPath = strMallocCat(pResource->dirResourcePath, fileNameWithExt);
            verifyPointer(pResource->outputPath, "Problem malloc outputPath in resource\n");
            free(fileNameWithExt);
        } else {
            return 1;
        }
    }
    pResource->isOutputPath = 1;
    return 0;
}

static int setDirAndOutputPath(Resource *pResource, const char *dirResourcePath) {
    int result = 0;
    pResource->dirResourcePath = strMallocCpy(dirResourcePath, strlen(dirResourcePath));
    verifyPointer(pResource->dirResourcePath, "Problem malloc directory path of resource");

    pResource->isDirResourcePath = 1;

    result = setOutputPath(pResource);

    return result;
}

int createFileResource(Resource *pResource, const char *dirResourcePath) {
    int result;

    result = setDirAndOutputPath(pResource, dirResourcePath);
    if (result != 0) {
        fprintf(stderr, "Don't found file extention of resource with url '%s'", pResource->pRequest->pUrlHelper->url);
        return -1;
    }

    if (saveRequestInFile(pResource->pRequest, pResource->outputPath) != CURLE_OK) {
        fprintf(stderr, "ERROR request : %s\n", pResource->pRequest->errBuf);
        return -1;
    }

    pResource->createdDate = getCurrentTime();
    verifyPointer(pResource->createdDate, "Problem get current time in createFileResource\n");
    pResource->isCreatedDate = 1;

    return 0;
}

void addResourceInfoInFile(Resource *pResource, const char *resourcesFile) {

}

void destroyResource(Resource *pResource) {

}
