#include "matrices.h"
#include "matrix.h"
#include "row_column.h"

int main(void)
{
    int rc = EXIT_SUCCESS;
    
    matrix_t matrix_a = { NULL, 0, 0, 0 };
    if ((rc = matrix_read(&matrix_a)))
        return rc;
    
    matrix_t matrix_b = { NULL, 0, 0, 0 };
    if ((rc = matrix_read(&matrix_b)))
    {
        matrix_free(&matrix_a);
        return rc;
    }
    
    matrix_do_square(&matrix_a);
    matrix_do_square(&matrix_b);

    if (matrix_a.num_row > matrix_b.num_row)
    {
        if ((rc = row_change_memory(&matrix_b, matrix_a.num_row - matrix_b.num_row)) ||
            (rc = column_change_memory(&matrix_b, matrix_a.num_row - matrix_b.num_row)))
            goto end;
    }
    else
    {
        if ((rc = row_change_memory(&matrix_a, matrix_b.num_row - matrix_a.num_row)) ||
            (rc = column_change_memory(&matrix_a, matrix_b.num_row - matrix_a.num_row)))
            goto end;
    }
    
    if (matrix_a.num_row > matrix_b.num_row)
        matrix_equalization(&matrix_b, matrix_a.num_row - matrix_b.num_row);
    else
        matrix_equalization(&matrix_a, matrix_b.num_row - matrix_a.num_row);
    
    if ((rc = matrices_read_degree(&matrix_a, &matrix_b)))
        goto end;
    matrices_zero_degree(&matrix_a, &matrix_b);
    
    matrix_t matrix_result = { NULL, matrix_a.num_row, matrix_a.num_column, 0 };
    if ((rc = matrix_allocate(&matrix_result)))
        goto end;
    
    matrices_mul(&matrix_a, &matrix_b, &matrix_result);
    matrix_print(&matrix_result);
    
    return EXIT_SUCCESS;
    
    end:
        matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    return rc;
}