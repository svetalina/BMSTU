#include "matrix.h"

int** allocate_matrix(int n, int m)
{
    int** matrix = malloc(n * sizeof(int*) + n * m * sizeof(int));
    if (!matrix)
        return NULL;
    
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)((char*) matrix + n * sizeof(int*) + i * m * sizeof(int));
    
    return matrix;
}

void read_matrix_size(matrix_t *matrix)
{
   scanf("%d ", &matrix->rows);
   scanf("%d ", &matrix->columns); 
}

void read_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->rows; j++)
            scanf("%d ", &matrix->matrix[i][j]);
}

void print_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->rows; j++)
            printf("%d ", matrix->matrix[i][j]);
}

void find_matrix_min(matrix_t *matrix)
{
    matrix->min = matrix->matrix[0][0];
    
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->rows; j++)
            if (matrix->matrix[i][j] < matrix->min)
                matrix->min = matrix->matrix[i][j];         
}

