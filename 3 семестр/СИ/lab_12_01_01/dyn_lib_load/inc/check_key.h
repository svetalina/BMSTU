#ifndef CHECK_KEY_H
#define CHECK_KEY_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#define ERROR_MEMORY 5
#define ERROR_FILTRATION_DATA 6
#define ERROR_EMPTY_FILTRATION 7

typedef int (__cdecl *fn_key_t)(const int *, const int *, int **, int **);
extern fn_key_t pkey;

int comparison_of_arrays(int *array_one, int *array_two, int len);
Suite *key_suite(Suite *s);

#endif