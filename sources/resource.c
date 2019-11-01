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
    char *fileNameWithExt = NULL;

    pResource->dirResourcePath = strMallocCpy(dirResourcePath, strlen(dirResourcePath));
    if (pResource->dirResourcePath == NULL) {
        destroyApp();
        errorQuit("Problem malloc directory path of resource");
    }

    if (pUrlHelper->isExtFile == 1) {
        pResource->outputPath = strMallocCat(pResource->dirResourcePath, pUrlHelper->fileName);
        if (pResource->outputPath == NULL) {
            destroyApp();
            errorQuit("Problem malloc output file path in resource\n");
        }
    } else {
        if (getExtFileByMimeType(pUrlHelper)) {
            fileNameWithExt = strMallocCat(pUrlHelper->fileName, pUrlHelper->extFile);
            pResource->outputPath = strMallocCat(pResource->dirResourcePath, fileNameWithExt);
        } else {
            return -1;
        }
    }

    return 0;
}

int createFileResource(Resource *pResource, const char *dirResourcePath) {
    if (setDirAndOutputPath(pResource, dirResourcePath) != 0) {
        fprintf(stderr, "Don't found file extention of resource with url '%s'", pResource->pRequest->pUrlHelper->url);
    }

    if (saveRequestInFile(pResource->pRequest, pResource->outputPath) != CURLE_OK) {
        fprintf(stderr, "ERROR request : %s\n", pResource->pRequest->errBuf);
        return -1;
    }


    
    // TODO : saveFileInResource with outputPath
}

void addResourceInfoInFile(Resource *pResource, const char *resourcesFile) {

}
