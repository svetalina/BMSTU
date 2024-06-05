#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "structure.h"

void items_free_memory(item_t **array, int size);
int items_read(FILE *f, item_t **array);
void items_print(item_t **array, int size);
void items_sort(item_t **array, int size);

#endif