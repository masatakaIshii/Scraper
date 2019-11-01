//
// Created by masat on 16/10/2019.
//

#include "resource.h"
#include "app.h"

Resource *initResource(const char *url, int depth, int maxDepth) {
    Resource *pResource = NULL;
    if (maxDepth < depth) {
        pResource = malloc(sizeof(Resource));
        if (pResource == NULL) {
            return NULL;
        }
        pResource->depth = depth;
        //pResource->createdDate = getCurrentTime();
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
    pResource->dirResourcePath = strMallocCpy(dirResourcePath, strlen(dirResourcePath));
    if (pResource->dirResourcePath == NULL) {
        destroyApp();
        errorQuit("");
    }

    if (pUrlHelper->isExtFile == 1) {
        pResource->outputPath = strMallocCat(pResource->dirResourcePath, pUrlHelper->fileName);
        if (pResource->outputPath == NULL) {
            destroyApp();
            return 0;
        }
    } else {
        getExtFileByMimeType(pUrlHelper);
    }

    return 1;
}

int createFileResource(Resource *pResource, const char *dirResourcePath) {
    if (setDirAndOutputPath(pResource, dirResourcePath) == 0) {

    }


    // TODO : create outputPath
    // TODO : saveFileInResource with outputPath
}

void addResourceInfoInFile(Resource *pResource, const char *resourcesFile) {

}
