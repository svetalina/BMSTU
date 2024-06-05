#ifndef CHECK_SORT_H
#define CHECK_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

typedef int (__cdecl *fn_comparison_integers_t)(const void *, const void *);
extern fn_comparison_integers_t pcompare_int;
typedef void (__cdecl *fn_mysort_t)(void *, size_t, size_t, int (*)(const void *, const void *));
extern fn_mysort_t pmysort;

int comparison_of_arrays(int *array_one, int *array_two, int len);
void check_sort(int *array_one, const int len_one, int *array_two, const int len_two);
Suite *sort_suite(Suite *s);

#endif