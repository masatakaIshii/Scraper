//
// Created by masat on 01/11/2019.
//

#ifndef SCRAPER_STRUCT_H
#define SCRAPER_STRUCT_H

#include <curl/curl.h>

/**
 * Possibility of option value
 * valueInt : integer's value of option
 * valueStr : string's value of option
 * listStr : list strings correspond to one option
 */
typedef union OptionValue {
    int valueInt;
    char *valueStr;
    char **listStr;
} OptionValue;

typedef enum TypeValue {
    OPTION_INT,
    OPTION_STR,
    OPTION_LIST_STR
} TypeValue;

typedef struct Option {
    char *name;
    OptionValue value;
    TypeValue typeValue;
    int nbrValue; // if the option value is listStr > 1
} Option;

typedef struct Action {
    char *name;
    char *url;
    Option **options;
    int numberOption;
} Action;

typedef struct Task {
    Action **actions;
    int numberActions;
    Option **options;
    int numberOptions;
} Task;


typedef struct Config {
    Action **actions;
    Task **task;
    char *content;
} Config;

typedef enum UrlHelperResponse {
    UH_OK,
    UH_NAME_PB,
} UHRes;

typedef struct UrlHelper {
    char *url;
    char *domainName;
    char *absPath;
    char *fileName;
    char *fileExt;
    int isUrl;
    int isDomainName;
    int isAbsPath;
    int isFileName;
    int isFileExt;
    UHRes result;
} UrlHelper;

typedef struct Request {
    CURL *pHandle;
    int isHandleInit;
    FILE *pFile;
    int isFileOpen;
    UrlHelper *pUrlHelper;
    short isUrlHelper;
    char *contentType;
    short isContentType;
    char errBuf[CURL_ERROR_SIZE];
} Request;

typedef struct Resource {
    short isRequest;
    Request *pRequest;
    short isDirResourcePath;
    char *dirResourcePath;
    short isOutputPath;
    char *outputPath;
    short isType;
    char *type;
    int depth;
    int maxDepth;
    short isCreatedDate;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} Resource;

typedef struct Session {
    int numberActions;
    char *name;
    Resource **resources;
    char *createdDate;
} Session;

typedef struct ListSession {
    Session **sessions;
    int capacity;
    int count;
} ListSession;

typedef struct Version {
    Action *action;
    Task *task;
    char *date;
    char *currentPath;
} Version;

typedef struct App {
    Config *pConfig;
    ListSession *listSession;
} App;

#endif //SCRAPER_STRUCT_H
