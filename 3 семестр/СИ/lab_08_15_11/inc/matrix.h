#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "structure.h"
 
int matrix_filling(char *const name, matrix_t *const mtr);
int res_matrix_create(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, int key);
int identity_matrix_create(matrix_t *mtr, matrix_t *res);
void matrix_addition(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res);
void matrix_multiplication(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res);
int matrix_inversion(matrix_t *const mtr, matrix_t *const res);
int matrix_print_main(char *const name, matrix_t *const res);

#endif