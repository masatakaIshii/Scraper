//
// Created by masat on 16/10/2019.
//

#ifndef SCRAPER_OPTION_H
#define SCRAPER_OPTION_H

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

#endif //SCRAPER_OPTION_H
