#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int **elements;
    size_t rows;
    size_t cols;
} matrix_t;

matrix_t *create_matrix(int row, int col);
void clear_matrix(matrix_t *mat);
void free_matrix(matrix_t *mat);
void print_matrix(matrix_t *mat);

#endif
