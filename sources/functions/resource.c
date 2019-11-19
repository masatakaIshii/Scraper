//
// Created by masat on 16/10/2019.
//
#include "../headers/resource.h"

static void initFieldsResource(Resource *pResource, Action *pAction, int depth);
static int setDirAndOutputPath(Resource *pResource, const char *dirResourcePath);
static int setOutputPath(Resource *pResource);
char **setLinks(Resource *pResource);

Resource *initResource(const char *url, Action *pAction, int depth) {
    Resource *pResource = NULL;
    if (pAction == NULL || pAction->maxDepth < depth || pAction->maxDepth < 0 || depth < 0) {
        return NULL;
    }
    pResource = malloc(sizeof(Resource));
    if (pResource == NULL) {
        return NULL;
    }
    initFieldsResource(pResource, pAction, depth);
    pResource->pRequest = initRequest(url);
    if (pResource->pRequest == NULL) {
        free(pResource);
        return NULL;
    }
    pResource->isRequest = 1;

    return pResource;
}

static void initFieldsResource(Resource *pResource, Action *pAction, int depth) {
    pResource->depth = depth;
    pResource->maxDepth = pAction->maxDepth;

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

/**
 * Function to set types to filter the type mime of request
 * @param pResource : structure of resource of url to get
 * @param types : the array of string that contain type mime to filter
 * @param count : the number of types
 * @return OK 0,<br>
 * ERROR -1
 */
int setTypesFilter(Resource *pResource, char **types, int count) {
    int i;

    pResource->numberType = count;
    pResource->type = malloc(sizeof(char *) * pResource->numberType);
    if (pResource->type == NULL) {
        fprintf(stderr, "Problem malloct pResource->type\n");
        return -1;
    }

    for (i = 0; i < pResource->numberType; i++) {
        pResource->type[i] = strMallocCpy(types[i], (int)strlen(types[i]));
        if (pResource->type[i] == NULL) {
            freeArrayString(pResource->type, i);
            fprintf(stderr, "Problem malloc pResource->type\n");
            return -1;
        }
    }
    return 0;
}

int createFileResource(Resource **pResource, const char *dirResourcePath, Action *pAction, int depth) {
    int result;

    result = setDirAndOutputPath(*pResource, dirResourcePath);
    if (result != 0) {
        fprintf(stderr, "\nDon't found file extention of resource with url '%s'\n", (*pResource)->pRequest->pUrlHelper->url);
        *pResource = NULL;
        return -1;
    }

    mkdirP((*pResource)->dirResourcePath);

    if (saveRequestInFile((*pResource)->pRequest, (*pResource)->outputPath) != CURLE_OK) {
        fprintf(stderr, "\nERROR request : %s\n", (*pResource)->pRequest->errBuf);
        *pResource = NULL;
        return -1;
    }

    if ((*pResource)->pRequest->isHandleInit) {
        clearPHandle((*pResource)->pRequest);
    }
    if ((*pResource)->pRequest->isFileOpen) {
        clearPFile((*pResource)->pRequest);
    }

    if (pAction->numberTypes > 0 && depth > 0) {
        if (checkIfStrIsInArrStr((*pResource)->pRequest->contentType, (const char **)pAction->types, pAction->numberTypes)) {
            unlink((*pResource)->outputPath);
            destroyResource(*pResource);
            *pResource = NULL;
            return -1;
        }
    }

    (*pResource)->createdDate = getCurrentTime();
    verifyPointer((*pResource)->createdDate, "Problem get current time in createFileResource\n");
    (*pResource)->isCreatedDate = 1;

    (*pResource)->links = setLinks(*pResource);

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
    char *dirResourcePathWithSlash = strMallocCat(pResource->dirResourcePath, "/");

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

/**
 * Search links in download file of resource
 * @param pResource
 * @return OK links : all link in http page, <br>
 * ERROR NULL;
 */
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

static void destroyRequestAndPath(Resource *pResource) {
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
}

void destroyResource(Resource *pResource) {
    if (pResource != NULL) {
        if (pResource->isCreatedDate == 1) {
            free(pResource->createdDate);
            pResource->isCreatedDate = 0;
        }
        destroyRequestAndPath(pResource);
        if (pResource->numberLinks > 0) {
            freeArrayString(pResource->links, pResource->numberLinks);
            pResource->numberLinks = 0;
        }
        if (pResource->numberType > 0) {
            freeArrayString(pResource->type, pResource->numberType);
        }

        free(pResource);
    }
}
