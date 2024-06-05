#ifndef CHECK_FIND_POS_MIN_H
#define CHECK_FIND_POS_MIN_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

int matrix_allocate(matrix_t *const matrix);
void matrix_free(matrix_t *const matrix);
int matrix_find_pos_min(matrix_t *const matrix);

void check_find_pos_min(matrix_t *const matrix, int pos_true);
Suite *find_pos_min_suite(Suite *s);

#endif