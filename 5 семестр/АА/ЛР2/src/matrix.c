#include <stdio.h>

#include "matrix.h"
#include "error.h"

matrix_t *create_matrix(int row, int col)
{
    matrix_t *new_matrix = malloc(sizeof(matrix_t));

    new_matrix->cols = col;
    new_matrix->rows = row;

    new_matrix->elements = malloc(sizeof(int*) * row);
    for (size_t i = 0; i < row; ++i)
        (new_matrix->elements)[i] = malloc(sizeof(int) * col);
	
	for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
			new_matrix->elements[i][j] = 0;

    return new_matrix;
}

int read_matrix(matrix_t **mat)
{	
	int rows, cols;
    printf("Введите количество строк матрицы: ");
    if (scanf("%d", &rows) != 1 || rows <= 0)
        return ERROR_READ_ROW;
    printf("Введите количество столбцов матрицы: ");
    if (scanf("%d", &cols) != 1 || cols <= 0)
        return ERROR_READ_COL;
	
	*mat = create_matrix(rows, cols);

    printf("Введите матрицу:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            if (scanf("%d", &((*mat)->elements[i][j])) != 1) {
                free_matrix(*mat);
                return ERROR_READ_ELEM;
            }
    }

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t *mat)
{
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j)
            printf("%d ", mat->elements[i][j]);
        printf("\n");
    }
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
