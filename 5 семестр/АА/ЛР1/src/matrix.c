#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

matrix_t *create_matrix(int row, int col)
{
    matrix_t *new_matrix = malloc(sizeof(matrix_t));

    new_matrix->cols = col;
    new_matrix->rows = row;

    new_matrix->elements = malloc(sizeof(int*) * row);
    for (size_t i = 0; i < row; ++i)
        (new_matrix->elements)[i] = malloc(sizeof(int) * col);

    return new_matrix;
}

void clear_matrix(matrix_t *mat)
{
    for (size_t i = 0; i < mat->rows; ++i)
        for (size_t j = 0; j < mat->cols; ++j)
            mat->elements[i][j] = -1;
}

void free_matrix(matrix_t *mat) {
    for (size_t i = 0; i < mat->rows; ++i)
        free(mat->elements[i]);

    free(mat->elements);
    free(mat);
}

void print_matrix(matrix_t *mat)
{
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j)
            printf("%d ", mat->elements[i][j]);
        printf("\n");
    }
}
