#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "structure.h"

int item_read(FILE *f, item_t *record);
void item_print(item_t *record);
void item_compare(item_t *record_1, item_t *record_2);

#endif