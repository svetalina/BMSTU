#include <math.h>
#include "row_column.h"

void row_delete(matrix_t *const matrix, int pos)
{
    for (int i = pos; i < matrix->num_row - 1; i++)
        for (int j = 0; j < matrix->num_column; j++)
            matrix->matrix[i][j] = matrix->matrix[i + 1][j];
    matrix->num_row--;
    free(matrix->matrix[matrix->num_row]);
}

void column_delete(matrix_t *const matrix, int pos)
{
    for (int j = pos; j < matrix->num_column - 1; j++)
        for (int i = 0; i < matrix->num_row; i++)
            matrix->matrix[i][j] = matrix->matrix[i][j + 1];
    matrix->num_column--;
}

int row_change_memory(matrix_t *const matrix, const int size_diff)
{
    int **tmp = realloc(matrix->matrix, (matrix->num_row + size_diff) * sizeof(int*));
    if (!tmp)
        return ERROR_MEMORY;
    matrix->matrix = tmp;

    for (size_t i = matrix->num_row; i < matrix->num_row + size_diff; i++)
    {
        int *tmp = malloc((matrix->num_column + size_diff) * sizeof(int));
        if (!tmp)
            return ERROR_MEMORY;

        matrix->matrix[i] = tmp;
    }

    return EXIT_SUCCESS;
}

int column_change_memory(matrix_t *const matrix, const int size_diff)
{
    for (size_t i = 0; i < matrix->num_column + size_diff; i++)
    {
        int *tmp = realloc(matrix->matrix[i], (matrix->num_column + size_diff) * sizeof(int));
        if (!tmp)
            return ERROR_MEMORY;

        matrix->matrix[i] = tmp;
    }

    return EXIT_SUCCESS;
}

int row_find_max(matrix_t *const matrix, int pos)
{
    int max = matrix->matrix[pos][0];
    for (int j = 0; j < matrix->num_column; j++)
        if (matrix->matrix[pos][j] > max)
            max = matrix->matrix[pos][j];

    return max;
}

int column_count_geometric_mean(matrix_t *const matrix, int pos)
{
    double gm = 1;
    for (int i = 0; i < matrix->num_row; i++)
        gm *= abs(matrix->matrix[i][pos]);
	
    gm = pow(gm, 1.0 / matrix->num_row);
    gm = (int)floor(gm);
	
    return gm;
}