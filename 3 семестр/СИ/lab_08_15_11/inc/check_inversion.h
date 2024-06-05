#ifndef CHECK_INVERSION_H
#define CHECK_INVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"
#include "errors.h"

double** allocate_matrix(int const n, int const m);
int identity_matrix_create(matrix_t *mtr, matrix_t *res);
int matrix_inversion(matrix_t *const mtr, matrix_t *const res);
int matrix_inversion_unzero_row_(matrix_t *const mtr, int ind, double *base);

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two);
void check_inversion(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, matrix_t *const mtr_true);
Suite *inversion_suite(Suite *s);

#endif