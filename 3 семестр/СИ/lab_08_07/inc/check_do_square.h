#ifndef CHECK_DO_SQUARE_H
#define CHECK_DO_SQUARE_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

int matrix_allocate(matrix_t *const matrix);
void matrix_free(matrix_t *const matrix);
void matrix_do_square(matrix_t *const matrix);
int matrix_find_pos_min(matrix_t *const matrix);
void row_delete(matrix_t *const matrix, int pos);
void column_delete(matrix_t *const matrix, int pos);

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two);
void check_do_square(matrix_t *const matrix, matrix_t *const matrix_true);
Suite *do_square_suite(Suite *s);

#endif