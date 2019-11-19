//
// Created by masat on 16/10/2019.
//

#include "../headers/config.h"


Config *initConfig() {
    Config *pConfig = NULL;

    pConfig = malloc(sizeof(Config));
    if (pConfig == NULL) {
        fprintf(stderr, "Problem malloc in initConfig\n");
        return NULL;
    }

    pConfig->content = NULL;
    pConfig->actions = NULL;
    pConfig->tasks = NULL;
    pConfig->actionsContent = NULL;
    pConfig->tasksContent = NULL;

    pConfig->numberTasks = 0;
    pConfig->numberActions = 0;

    return pConfig;
}


Action *initAction() {
    Action *action = malloc(sizeof(Action));
    if (action == NULL) {
        return NULL;
    }

    action->name = NULL;
    action->url = NULL;
    action->maxDepth = 0;
    action->types = NULL;
    action->numberTypes = 0;

    return action;
}

Task *initTask() {
    Task *task = malloc(sizeof(Task));
    if (task == NULL) {
        return NULL;
    }

    task->name = NULL;
    task->hour = 0;
    task->minute = 0;
    task->second = 0;
    task->numberActionsNames = 0;
    task->actionsNames = NULL;

    return task;
}

static char *getPartActionsContent(char *content) {
    char *actionsContent = NULL;
    char *endActionsPart = strstr(content, "==");
    if (endActionsPart == NULL) {
        return NULL;
    }

    actionsContent = strMallocCpy(content + 1, (int) (endActionsPart - content) - 1);
    if (actionsContent == NULL) {
        return NULL;
    }

    return actionsContent;
}

static char *getPartTasksContent(char *content) {
    char *tasksContent = NULL;
    char *startTaskPart = strstr(content, "==");

    tasksContent = strMallocCpy(startTaskPart + 2, strlen(startTaskPart) - 2);
    if (tasksContent == NULL) {
        return NULL;
    }

    return tasksContent;
}

static int getActionsAndTasksContents(Config *pConfig) {
    pConfig->actionsContent = getPartActionsContent(pConfig->content);
    if (pConfig->actionsContent == NULL) {
        return -1;
    }
    pConfig->tasksContent = getPartTasksContent(pConfig->content);
    if (pConfig->tasksContent == NULL) {
        return -1;
    }

    return 0;
}

static int getVersioningNumber(char *versioning) {
    if (strcmp(versioning, "on") == 0) {
        return 1;
    }

    return 0;
}

static int checkIfOptionValueIsInteger(char *content, char *optionName) {
    char *potentialNumber = NULL;
    int result = 0;
    potentialNumber = getOptValueByContent(content, optionName);
    result = strtol(potentialNumber, NULL, 10);

    free(potentialNumber);
    return result;
}

static Action *parseAction(char *actionContent) {

    char *versioning = NULL;
    Action *action = initAction();
    if (action == NULL) {
        return NULL;
    }

    action->name = getOptValueByContent(actionContent, "name");
    action->url = getOptValueByContent(actionContent, "url");
    action->maxDepth = checkIfOptionValueIsInteger(actionContent, "max-depth");

    versioning = getOptValueByContent(actionContent, "versioning");
    if (versioning != NULL) {
        action->versioning = getVersioningNumber(versioning);
        free(versioning);
    }
    action->types = getArrValuesInParenthesisOfContent(actionContent, ",", &action->numberTypes);

    return action;
}

static Action **getActionsByFileContent(char *actionsContent, int *numberActions) {
    int i;
    char **splitContent = strSplit(actionsContent, "=", numberActions);
    Action **actions = malloc(sizeof(Action *) * (*numberActions));
    if (actions == NULL) {
        return NULL;
    }
    for (i = 0; i < *numberActions; i++) {
        actions[i] = parseAction(splitContent[i]);
        if (actions[i] == NULL) {
            free(splitContent);
            return NULL;
        }
    }

    free(splitContent);

    return actions;
}

static Task *parseTask(char *tasksContent) {

    Task *task = initTask();
    if (task == NULL) {
        return NULL;
    }
    task->name = getOptValueByContent(tasksContent, "name");
    if (task->name == NULL) {
        free(task);
        return NULL;
    }
    task->hour = checkIfOptionValueIsInteger(tasksContent, "hour");
    task->minute = checkIfOptionValueIsInteger(tasksContent, "minute");
    task->second = checkIfOptionValueIsInteger(tasksContent, "second");
    task->actionsNames = getArrValuesInParenthesisOfContent(tasksContent, ",", &task->numberActionsNames);

    return task;
}

static Task **getTasksByFileContent(char *taskContent, int *numberTasks) {
    int i;
    char **splitContent = strSplit(taskContent, "==", numberTasks);
    Task **tasks = malloc(sizeof(Task *) * (*numberTasks));
    if (tasks == NULL) {
        return NULL;
    }
    for (i = 0; i < *numberTasks; i++) {
        tasks[i] = parseTask(splitContent[i]);
        if (tasks[i] == NULL) {
            free(splitContent);
            return NULL;
        }
    }

    free(splitContent);

    return tasks;
}

static int parseActionsAndTasks(Config *pConfig) {

    pConfig->actions = getActionsByFileContent(pConfig->actionsContent, &pConfig->numberActions);
    if (pConfig->actions == NULL) {
        return -1;
    }
    free(pConfig->actionsContent);
    pConfig->actionsContent = NULL;

    pConfig->tasks = getTasksByFileContent(pConfig->tasksContent, &pConfig->numberTasks);
    if (pConfig->tasks == NULL) {
        return -1;
    }
    free(pConfig->tasksContent);
    pConfig->tasksContent = NULL;

    return 0;
}

static int runActionByTask(Task *task, Action **actions, int numberAction) {
    int i;
    int j;

    for (i = 0; i < task->numberActionsNames; i++) {
        for (j = 0; j < numberAction; j++) {
            if (strcmp(task->actionsNames[i], actions[i]->name) == 0) {
                // initSession;
            }
        }
    }

    return 0;
}

int fillConfig(Config *pConfig) {

    pConfig->content = getContentInFile("configuration.sconf", "rb");
    if (pConfig->content == NULL) {
        fprintf(stderr, "Problem get content file configuration.sconf");
        return -1;
    }

    if (getActionsAndTasksContents(pConfig) == -1) {
        return -1;
    }

    if (parseActionsAndTasks(pConfig) == -1) {
        return -1;
    }

    return 0;
}


int runAllTasks(Config *pConfig) {
    int i;

    for (i = 0; i < pConfig->numberTasks; i++) {
        if (runActionByTask(pConfig->tasks[i], pConfig->actions, pConfig->numberActions) == -1) {
            return -1;
        }
    }
    return 0;
}


void destroyAction(Action *action) {
    if (action->name != NULL) {
        free(action->name);
    }
    if (action->url != NULL) {
        free(action->url);
    }
    if (action->numberTypes > 0) {
        freeArrayString(action->types, action->numberTypes);
    }
    free(action);
}

void destroyTask(Task *task) {
    int i;

    if (task->numberActionsNames > 0) {
        for (i = 0; i < task->numberActionsNames; i++) {
            free(task->actionsNames[i]);
        }
    }

    if (task->name != NULL) {
        free(task->name);
    }

    free(task);
}

static void destroyActionsAndTask(Config *pConfig) {
    int i;
    if (pConfig->numberActions > 0) {
        for (i = 0; i < pConfig->numberActions; i++) {
            destroyAction(pConfig->actions[i]);
        }
        pConfig->numberActions = 0;
    }

    if (pConfig->numberTasks > 0) {
        for (i = 0; i < pConfig->numberTasks; i++) {
            destroyTask(pConfig->tasks[i]);
        }
    }
}

void destroyConfig(Config *pConfig) {

    if (pConfig->content != NULL) {
        free(pConfig->content);
    }

    if (pConfig->actionsContent != NULL) {
        free(pConfig->actionsContent);
    }

    if (pConfig->tasksContent != NULL) {
        free(pConfig->tasksContent);
    }
    destroyActionsAndTask(pConfig);

    free(pConfig);
}