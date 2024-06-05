#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct {
    int **elements;
    size_t rows;
    size_t cols;
} matrix_t;

matrix_t *create_matrix(int row, int col);
int read_matrix(matrix_t **mat);
void clear_matrix(matrix_t *mat);
void free_matrix(matrix_t *mat);
void print_matrix(matrix_t *mat);

#endif
