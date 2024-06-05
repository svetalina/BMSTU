#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_NAME -2
#define ERROR_MASS -3
#define ERROR_VOLUME -4
#define ERROR_SYMBOL -5

#define NAME_SIZE 27

typedef struct
{
    char name[NAME_SIZE];
    float mass;
    float volume;
} item_t;

int item_read(FILE *f, item_t *record);
void item_print(item_t *record);
void item_compare(item_t *record_1, item_t *record_2);

#endif