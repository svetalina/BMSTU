#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "errors.h"

int matrix_allocate(matrix_t *const matrix);
void matrix_free(matrix_t *const matrix);
int matrix_read(matrix_t *const matrix);
int matrix_input_size(matrix_t *const matrix);
int matrix_input(matrix_t *const matrix);
int matrix_input_degree(matrix_t *const matrix);
void matrix_print(matrix_t *const matrix);
void matrix_do_square(matrix_t *const matrix);
void matrix_equalization(matrix_t *const matrix, int diff);
void matrix_zero_degree(matrix_t *const matrix);
void matrix_copy(matrix_t *const matrix, matrix_t *const matrix_copied);
void matrix_mul(matrix_t *const matrix_a, matrix_t *const matrix_b, matrix_t *const matrix_result);

#endif