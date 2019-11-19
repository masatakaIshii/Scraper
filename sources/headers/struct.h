//
// Created by masat on 01/11/2019.
//

#ifndef SCRAPER_STRUCT_H
#define SCRAPER_STRUCT_H

#include <curl/curl.h>

typedef struct Time {
    int seconds;
    int minutes;
    int hours;
    int years;
} Time;

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
    int maxDepth;
    int versioning;
    char **types;
    int numberTypes;
} Action;

typedef struct Task {
    char *name;
    int hour;
    int minute;
    int second;
    char **actionsNames;
    int numberActionsNames;
} Task;


typedef struct Config {
    int numberActions;
    Action **actions;
    int numberTasks;
    Task **tasks;
    char *content;
    char *actionsContent;
    char *tasksContent;
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

typedef struct UrlSearcher {
    char *protocolCom;
    char *rootPath;
    char *page;
    char *currentPage;
    char *pointOccur;
    char *start;
    char *end;
    char container;
    int position;
    int isPage;
    int isProtocolCom;
    int isRootPath;
    int isPointOccur;
} UrlSearcher;

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
    char **type;
    int numberType;
    int depth;
    int maxDepth;
    short isCreatedDate;
    char *createdDate;
    long size;
    int numberLinks;
    char **links;
} Resource;

typedef struct Session {
    char *actionName;
    char *taskName;
    char *sessionDirPath;
    Resource *resources;
    unsigned long dateSeconds;
    char *createdDate;
} Session;

typedef struct Version {
    Action *action;
    Task *task;
    char *date;
    char *currentPath;
} Version;

typedef struct App {
    Config *pConfig;
    Session *session;
} App;

#endif //SCRAPER_STRUCT_H
