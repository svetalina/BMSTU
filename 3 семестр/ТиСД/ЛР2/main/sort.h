#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>
#include "structures.h"

void swap(short int table, void *val1, void *val2);
int comparator_keys(const void* val1, const void* val2);
int comparator_table(const void* val1, const void* val2);
void bubble_sort(const int size, void *arr, int (*comparator)(const void *val1, const void *val2), short int table, size_t size_bytes);

#endif
