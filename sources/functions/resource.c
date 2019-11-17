//
// Created by masat on 16/10/2019.
//
#include "../headers/resource.h"

static void initFieldsResource(Resource *pResource, int depth, int maxDepth);
static int setDirAndOutputPath(Resource *pResource, const char *dirResourcePath);
static int setOutputPath(Resource *pResource);
char **setLinks(Resource *pResource);

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

static void initFieldsResource(Resource *pResource, int depth, int maxDepth) {
    pResource->depth = depth;
    pResource->maxDepth = maxDepth;

    pResource->isCreatedDate = 0;
    pResource->createdDate = NULL;

    pResource->isDirResourcePath = 0;
    pResource->dirResourcePath = NULL;

    pResource->isOutputPath = 0;
    pResource->outputPath = NULL;

    pResource->numberType = 0;
    pResource->type = NULL;

    pResource->isRequest = 0;

    pResource->size = 0;
    pResource->numberLinks = 0;
    pResource->links = NULL;
}

void setTypesFilter(Resource *pResource, char **type, int count) {
    pResource->type = type;
    pResource->numberType = count;
}

int createFileResource(Resource *pResource, const char *dirResourcePath, const char **filter, int depth) {
    int result;

    result = setDirAndOutputPath(pResource, dirResourcePath);
    if (result != 0) {
        fprintf(stderr, "\nDon't found file extention of resource with url '%s'\n", pResource->pRequest->pUrlHelper->url);
        return -1;
    }

    mkdirP(pResource->dirResourcePath);

    if (saveRequestInFile(pResource->pRequest, pResource->outputPath) != CURLE_OK) {
        fprintf(stderr, "\nERROR request : %s\n", pResource->pRequest->errBuf);
        return -1;
    }
    if (pResource->pRequest->isHandleInit) {
        clearPHandle(pResource->pRequest);
    }
    if (pResource->pRequest->isFileOpen) {
        clearPFile(pResource->pRequest);
    }

    pResource->createdDate = getCurrentTime();
    verifyPointer(pResource->createdDate, "Problem get current time in createFileResource\n");
    pResource->isCreatedDate = 1;

    pResource->links = setLinks(pResource);

    return 0;
}

static int setDirAndOutputPath(Resource *pResource, const char *dirResourcePath) {
    int result = 0;
    pResource->dirResourcePath = strMallocCpy(dirResourcePath, (int)strlen(dirResourcePath));
    verifyPointer(pResource->dirResourcePath, "Problem malloc directory path of resource\n");

    pResource->isDirResourcePath = 1;

    result = setOutputPath(pResource);

    return result;
}

static int setOutputPath(Resource *pResource) {
    UrlHelper *pUrlHelper = pResource->pRequest->pUrlHelper;
    char *dirResourcePathWithSlash = strMallocCat(pResource->dirResourcePath, "/");;

    if (pUrlHelper->isFileExt == 0 || pUrlHelper->isFileName == 0) {
        if (getFileExtByMimeType(pResource->pRequest, pResource->dirResourcePath) != 1) { // fetch extension file by mime type search in conditions and list fileExt / mimeType
            return -1;
        }
    }
    pResource->outputPath = strMallocCat(dirResourcePathWithSlash, pUrlHelper->fileName);
    verifyPointer(pResource->outputPath, "Problem malloc output file path in resource\n");
    pResource->isOutputPath = 1;

    free(dirResourcePathWithSlash);

    return 0;
}

char **setLinks(Resource *pResource) {
    Request *pRequest = pResource->pRequest;
    UrlHelper *pUrlHelper = pRequest->pUrlHelper;
    char **links = NULL;
    if (pUrlHelper->isUrl != 1) {
        fprintf(stderr, "ERROR in setLinks, url is not set\n");
        return NULL;
    }
    if (pRequest->isContentType != 1) {
        fprintf(stderr, "ERROR in setLinks, content type is not set\n");
        return NULL;
    }
    if (pResource->isOutputPath != 1) {
        fprintf(stderr, "ERROR in setLinks, output path is not set\n");
        return NULL;
    }
    links = getAllUrlsInPage(pUrlHelper->url, pRequest->contentType, pResource->outputPath, &pResource->numberLinks, pResource->dirResourcePath);

    return links;
}

void addResourceInfoInFile(Resource *pResource, const char *resourcesFile) {

}

void destroyResource(Resource *pResource) {
    if (pResource->isCreatedDate == 1) {
        free(pResource->createdDate);
        pResource->isCreatedDate = 0;
    }
    if (pResource->isOutputPath == 1) {
        free(pResource->outputPath);
        pResource->isOutputPath = 0;
    }
    if (pResource->isDirResourcePath == 1) {
        free(pResource->dirResourcePath);
        pResource->isDirResourcePath = 0;
    }
    if (pResource->isRequest == 1) {
        destroyRequest(pResource->pRequest);
        pResource->isRequest = 0;
    }
    if (pResource->numberLinks > 0) {
        freeArrayString(pResource->links, pResource->numberLinks);
        pResource->numberLinks = 0;
    }
    if (pResource->numberType > 0) {
        freeArrayString(pResource->type, pResource->numberType);
    }

    free(pResource);
}
