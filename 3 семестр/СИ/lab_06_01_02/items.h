#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_STRUCT_SIZE -6

#define ARRAY_SIZE 15

int items_read(FILE *f, item_t *array);
void items_print(item_t *array, int size);
void items_sort(item_t *array, int size);

#endif