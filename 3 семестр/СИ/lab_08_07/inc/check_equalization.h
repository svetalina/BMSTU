#ifndef CHECK_EQUALIZATION
#define CHECK_EQUALIZATION

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

int matrix_allocate(matrix_t *const matrix);
void matrix_free(matrix_t *const matrix);
void matrix_equalization(matrix_t *const matrix, int diff);
int row_find_max(matrix_t *const matrix, int pos);
int column_count_geometric_mean(matrix_t *const matrix, int pos);

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two);
void check_equalization(matrix_t *const matrix, int diff, matrix_t *const matrix_true);
Suite *equalization_suite(Suite *s);

#endif