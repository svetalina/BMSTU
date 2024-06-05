#include "matrix.h"
#include "row_column.h"

int matrix_allocate(matrix_t *const matrix)
{
    matrix->matrix = calloc(matrix->num_row, sizeof(int *));
    if (!matrix->matrix)
        return ERROR_MEMORY;

    for (size_t i = 0; i < matrix->num_row; i++)
    {
        matrix->matrix[i] = malloc(matrix->num_column * sizeof(int));
        if (!matrix->matrix[i])
        {
            matrix_free(matrix);
            return ERROR_MEMORY;
        }
    }

    return EXIT_SUCCESS;
}

void matrix_free(matrix_t *const matrix)
{
    for (size_t i = 0; i < matrix->num_row; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
}

int matrix_read(matrix_t *const matrix)
{
    int rc;
    
    if ((rc = matrix_input_size(matrix)))
        return rc;
    
    if (matrix_allocate(matrix))
        return ERROR_MEMORY;
    
    if ((rc = matrix_input(matrix)))
    {
        matrix_free(matrix);
        return rc;
    }
    
    return EXIT_SUCCESS;    
}

int matrix_input_size(matrix_t *const matrix)
{
    if (scanf("%d", &matrix->num_row) != 1)
        return ERROR_SIZE_ROW;
    if (scanf("%d", &matrix->num_column) != 1)
        return ERROR_SIZE_COLUMN;
	
    if (matrix->num_row <= 0 || matrix->num_column <= 0)
        return ERROR_SIGN_SIZE;

    return EXIT_SUCCESS;
}

int matrix_input(matrix_t *const matrix)
{
    for (size_t i = 0; i < matrix->num_row; i++)
        for (size_t j = 0; j < matrix->num_column; j++)
            if (scanf("%d", &matrix->matrix[i][j]) != 1)
                return ERROR_ELEMENT;

    return EXIT_SUCCESS;
}

int matrix_input_degree(matrix_t *const matrix)
{
    if (scanf("%d", &matrix->degree) != 1)
        return ERROR_DEGREE;
    if (matrix->degree < 0)
        return ERROR_SIGN_DEGREE;

    return EXIT_SUCCESS;
}

void matrix_print(matrix_t *const matrix)
{
    for (size_t i = 0; i < matrix->num_row; i++)
    {
        for (size_t j = 0; j < matrix->num_column; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
    
    matrix_free(matrix);
}

int matrix_find_pos_min(matrix_t *const matrix)
{
    int min = matrix->matrix[0][0], pos = 0;
    for (size_t j = 0; j < matrix->num_column; j++)
    {
        for (size_t i = 0; i < matrix->num_row; i++)
        {
            if (matrix->matrix[i][j] < min)
            {
                min = matrix->matrix[i][j];
                pos = (matrix->num_row > matrix->num_column) ? i : j;
            }
        }
    }
    
    return pos;
}

void matrix_do_square(matrix_t *const matrix)
{
    int type_delete = matrix->num_row - matrix->num_column;
	
    for (size_t k = 0; k < abs(type_delete); k++)
    {
        int pos = matrix_find_pos_min(matrix);

        if (type_delete > 0) 
            row_delete(matrix, pos);
        else 
            column_delete(matrix, pos);
    }
}

void matrix_equalization(matrix_t *const matrix, int diff)
{
    int start_row = matrix->num_row, start_column = matrix->num_column;
    for (size_t i = start_row; i < start_row + diff; i++)
    {
        for (size_t j = 0;  j < matrix->num_column; j++)
            matrix->matrix[i][j] = column_count_geometric_mean(matrix, j);
        matrix->num_row++;
    }
		
    for (size_t j = start_column; j < start_column + diff; j++)
    {
        for (size_t i = 0;  i < matrix->num_row; i++)
            matrix->matrix[i][j] = row_find_max(matrix, i);
        matrix->num_column++;
    }
}

void matrix_zero_degree(matrix_t *const matrix)
{
    for (size_t i = 0; i < matrix->num_row; i++)
        for (size_t j = 0; j < matrix->num_column; j++)
        {
            if (i == j)
                matrix->matrix[i][j] = 1;
            else
                matrix->matrix[i][j] = 0;
        }
}

void matrix_copy(matrix_t *const matrix, matrix_t *const matrix_copied)
{
    for (size_t i = 0; i < matrix->num_row; i++)
        for (size_t j = 0; j < matrix->num_column; j++)
            matrix_copied->matrix[i][j] = matrix->matrix[i][j];
}

void matrix_mul(matrix_t *const matrix_a, matrix_t *const matrix_b, matrix_t *const matrix_result)
{
    for (int i = 0; i < matrix_a->num_row; i++)
    {
        for (int j = 0; j < matrix_b->num_column; j++)
        {
            matrix_result->matrix[i][j] = 0;
            for (int k = 0; k < matrix_a->num_column; k++)
                matrix_result->matrix[i][j] += matrix_a->matrix[i][k] * matrix_b->matrix[k][j];
        }
    }
}