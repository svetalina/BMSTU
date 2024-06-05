#include "file.h"

int file_read_sizes(FILE *f, matrix_t *const mtr)
{
    if (fscanf(f, "%d", &mtr->i_size) != 1)
        return ERROR_ROW_SIZE;
    if (fscanf(f, "%d", &mtr->j_size) != 1)
        return ERROR_COLUMN_SIZE;
    
    return EXIT_SUCCESS;
}

int file_read_value(FILE *f, matrix_t *const mtr)
{
    for (size_t i = 0; i < mtr->i_size; i++)
        for (size_t j = 0; j < mtr->j_size; j++)
            if (fscanf(f, "%lf", &mtr->mtr[i][j]) != 1)
                return ERROR_VALUE;
    
    return EXIT_SUCCESS;
}

void file_print_result(FILE *f, matrix_t *const res)
{
    fprintf(f, "%d %d\n", res->i_size, res->j_size);
    for (size_t i = 0; i < res->i_size; i++)
    {
        for (size_t j = 0; j < res->j_size; j++)
            fprintf(f, "%lf ", res->mtr[i][j]);
        fprintf(f, "\n");
    }
}