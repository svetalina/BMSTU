#ifndef CHECK_MUL_H
#define CHECK_MUL_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

int matrix_allocate(matrix_t *const matrix);
void matrix_free(matrix_t *const matrix);
void matrix_mul(matrix_t *const matrix_a, matrix_t *const matrix_b, matrix_t *const matrix_result);

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two);
void check_mul(matrix_t *const matrix_one, matrix_t *const matrix_two, matrix_t *const matrix_result, matrix_t *const matrix_true);
Suite *mul_suite(Suite *s);

#endif