//
// Created by masat on 12/11/2019.
//

#include "../headers/listArray.h"
static int expandListStrCapacity(ListStr *listStr);

/**
 * Initialize ListStr structure that represents list of string
 * @param initCapacity : init capacity that grown * 2 when this is exceed
 * @return OK listStr : pointer of list of string, ERROR NULL<br>
 * ERROR1 : can be the capacity that is less than 1<br>
 * ERROR2 : can be problem of malloc
*/
ListStr *initListStr(int initCapacity) {
    ListStr *listStr = malloc(sizeof(ListStr));
    if (listStr == NULL) {
        return NULL;
    }
    listStr->capacity = initCapacity;
    listStr->count = 0;
    listStr->arrStr = (listStr->capacity > 0) ? malloc(sizeof(char *) * listStr->capacity) : NULL;
    if (listStr->arrStr == NULL) {
        fprintf(stderr, "ERROR in initListStr : the capacity have to be more than 0\n");
        free(listStr);
        return NULL;
    }

    return listStr;
}

/**
 * Add string in list
 * @param listStr : pointer of structure ListStr
 * @param strToAdd : string to add in list
 * @return OK 1 : string is add to the list,<br>
 * ERROR 0 : problem to add and listStr is destroy
 */
int listStrAdd(ListStr *listStr, const char *strToAdd) {

    if (listStr->count == listStr->capacity) {
        if (expandListStrCapacity(listStr) == 0) {
            destroyListStr(listStr);
            return 0;
        }
    }

    listStr->arrStr[listStr->count] = calloc(strlen(strToAdd) + 1, sizeof(char));
    if (listStr->arrStr[listStr->count] == NULL) {
        destroyListStr(listStr);
        return 0;
    }

    strcpy(listStr->arrStr[listStr->count], strToAdd);

    listStr->count++;
    return 1;
}

/**
 * Expand the list of string when the capacity is exceed
 * @param listStr : the pointer of structure ListStr
 * @return OK 1 : the capacity of list is expand, <br>
 * ERROR 0 : problem to expand the capacity and list is destroy
 */
static int expandListStrCapacity(ListStr *listStr) {
    int i;
    char **newArrStr = NULL;

    listStr->capacity *= 2;
    newArrStr = malloc(sizeof(char*) * listStr->capacity);
    if (newArrStr == NULL) {
        destroyListStr(listStr);
        return 0;
    }
    for (i = 0; i < listStr->count; i++) {
        newArrStr[i] = calloc(strlen(listStr->arrStr[i]) + 1, sizeof(char));
        if (newArrStr[i] == NULL) {
            freeArrayString(newArrStr, i);
            destroyListStr(listStr);
            return 0;
        }
        strcpy(newArrStr[i], listStr->arrStr[i]);
    }
    free(listStr->arrStr);
    listStr->arrStr = newArrStr;

    return 1;
}

const char* listStrGet(ListStr *listStr, int index) {
    if (index >= listStr->count) {
        fprintf(stderr, "ERROR in listStrGet : the value of index %d is to high, you have to choose unsigned int until %d\n", index, listStr->count - 1);
        return NULL;
    }

    return  listStr->arrStr[index];
}

void destroyListStr(ListStr *listStr) {
    int i;

    for (i = 0; i < listStr->count; i++) {
        free(listStr->arrStr[i]);
    }
    free(listStr->arrStr);
    free(listStr);
}

char **copyArrStr(char **arrStr, int count) {
    int i;
    char **newArrStr = malloc(sizeof(char*) * count);
    if (newArrStr == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        newArrStr[i] = calloc(strlen(arrStr[i]) + 1, sizeof(char));
        if (newArrStr[i] == NULL) {
            freeArrayString(newArrStr, i);
            return NULL;
        }
        strcpy(newArrStr[i], arrStr[i]);
    }

    return newArrStr;
}

char **destroyListStrAndReturnArrStr(ListStr *listStr, int *count) {
    char **arrStr = copyArrStr(listStr->arrStr, listStr->count);
    if (arrStr == NULL) {
        return NULL;
    }

    *count = listStr->count;

    destroyListStr(listStr);

    return arrStr;
}
