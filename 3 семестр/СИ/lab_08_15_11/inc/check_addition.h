#ifndef CHECK_ADDITION_H
#define CHECK_ADDITION_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

double** allocate_matrix(int const n, int const m);
void matrix_addition(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res);

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two);
void check_addition(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, matrix_t *const mtr_true);
Suite *addition_suite(Suite *s);

#endif