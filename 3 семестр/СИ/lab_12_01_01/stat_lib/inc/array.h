#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_SYMBOL 3
#define ERROR_MEMORY 5
#define ERROR_FILTRATION_DATA 6
#define ERROR_EMPTY_FILTRATION 7

int array_read(int **pb_array, int **pe_array, FILE *const f);
int array_find_last_neg(const int *const begin, const int *const end);
void array_fill_new(const int *begin, const int *end, int **begin_fa, int **end_fa);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));

#endif
