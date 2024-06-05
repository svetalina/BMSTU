#ifndef CHECK_SORT_H
#define CHECK_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

int items_change_memory(item_t **array, int size);
void items_free_memory(item_t **array, int size);
void items_sort(item_t **array, int size);
void item_compare(item_t *record_1, item_t *record_2);

int comparison_of_array(item_t **array_1, int size_1, item_t **array_true, int size_true);
void check_sort(item_t **array_1, int size_1, item_t **array_true, int size_true);
Suite *sort_suite(Suite *s);

#endif
