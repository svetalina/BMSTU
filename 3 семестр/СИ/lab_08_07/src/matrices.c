#include "matrices.h"
#include "matrix.h"

int matrices_read_degree(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    int rc;
    
    if ((rc = matrix_input_degree(matrix_a)))
        return rc;

    if ((rc = matrix_input_degree(matrix_b)))
        return rc;

    return EXIT_SUCCESS;
}

void matrices_zero_degree(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    if (matrix_a->degree == 0)
        matrix_zero_degree(matrix_a);
	
    if (matrix_b->degree == 0)
        matrix_zero_degree(matrix_b);
}

int matrices_mul(matrix_t *const matrix_a, matrix_t *const matrix_b, matrix_t *const matrix_result)
{
    matrix_t tmp = { NULL, matrix_a->num_row, matrix_a->num_column, 0 };
    if ((matrix_allocate(&tmp)))
        return ERROR_MEMORY;
	
    matrix_copy(matrix_a, &tmp);
    matrix_copy(matrix_a, matrix_result);
	
    for (size_t i = 1; i < matrix_a->degree; i++)
    {
        matrix_mul(&tmp, matrix_a, matrix_result);
        matrix_copy(matrix_result, &tmp);
    }
	
    for (size_t i = 0; i < matrix_b->degree; i++)
    {
        matrix_mul(&tmp, matrix_b, matrix_result);
        matrix_copy(matrix_result, &tmp);
    }
    
    matrix_free(&tmp);
    matrix_free(matrix_a);
    matrix_free(matrix_b);
    
    return EXIT_SUCCESS;
}
