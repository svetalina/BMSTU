#ifndef CHECK_KEY_H
#define CHECK_KEY_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#define ERROR_MEMORY 5
#define ERROR_FILTRATION_DATA 6
#define ERROR_EMPTY_FILTRATION 7

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int array_find_last_neg(const int *const begin, const int *const end);
void array_fill_new(const int *begin, const int *end, int **begin_fa, int **end_fa);

int comparison_of_arrays(int *array_one, int *array_two, int len);
Suite *key_suite(Suite *s);

#endif