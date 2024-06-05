#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

int** allocate_matrix(int n, int m);
void read_matrix_size(matrix_t *matrix);
void read_matrix(matrix_t *matrix);
void print_matrix(matrix_t *matrix);
void find_matrix_min(matrix_t *matrix);

#endif