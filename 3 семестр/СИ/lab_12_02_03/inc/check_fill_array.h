#ifndef CHECK_FILL_ARRAY_H
#define CHECK_FILL_ARRAY_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int compare_arrays(int *arr_1, int size_1, int *arr_2, int size_2);
Suite *fill_array_suite(Suite *s);

#endif