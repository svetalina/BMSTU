#ifndef MATRICES_H
#define MATRICES_H

#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "errors.h"

int matrices_read_degree(matrix_t *const matrix_a, matrix_t *const matrix_b);
void matrices_zero_degree(matrix_t *const matrix_a, matrix_t *const matrix_b);
int matrices_mul(matrix_t *const matrix_a, matrix_t *const matrix_b, matrix_t *const matrix_result);

#endif