#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_SYMBOL 3
#define ERROR_MEMORY 5
#define ERROR_FILTRATION_DATA 6
#define ERROR_EMPTY_FILTRATION 7

int comparison_integers(const void *el_1, const void *el_2);
int array_read(int **pb_array, int **pe_array, FILE *const f);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));

#endif
