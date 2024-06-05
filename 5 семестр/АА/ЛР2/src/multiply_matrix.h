#ifndef MULTIPLY_MATRIX_H
#define MULTIPLY_MATRIX_H

#include "matrix.h"

matrix_t *mul_matrix_def(matrix_t *first_mat, matrix_t *second_mat);
matrix_t *mul_matrix_vinograd(matrix_t *first_mat, matrix_t *second_mat);
matrix_t *mul_matrix_vinograd_opt(matrix_t *first_mat, matrix_t *second_mat);

int multiply_matrix(int action);


#endif
