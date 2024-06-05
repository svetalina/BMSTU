#include "memory.h"

void free_std_matrix(std_matrix_t matrix)
{
    for (int i = 0; i < matrix.x_size; i++)
        free(matrix.matrix[i]);
    free(matrix.matrix);
}

void free_list(list_t list)
{
    free(list.arr);
}

void free_sparse_matrix(sparse_matrix_t matrix)
{
    free(matrix.a);
    free(matrix.ia);
    free(matrix.ja);
}

void free_all(std_matrix_t std_matrix, sparse_matrix_t sparse_matrix, list_t list)
{
    free_list(list);
    free_std_matrix(std_matrix);
    free_sparse_matrix(sparse_matrix);
}


int allocate_std_matrix(std_matrix_t *matrix)
{
    int **tmp = calloc(matrix->x_size, sizeof(int*));
    if (!tmp)
        return ERROR_MEMORY;

    for (int i = 0; i < matrix->x_size; i++)
    {
        tmp[i] = calloc(matrix->y_size, sizeof(int));

        if (!tmp[i])
        {
            free_std_matrix(*matrix);
            return ERROR_MEMORY;
        }
    }
    
    matrix->matrix = tmp;

    return EXIT_SUCCESS;
}

int allocate_list(list_t *list)
{
    list_t tmp;
    
    tmp.arr = calloc(list->size, sizeof(int));
    if (!tmp.arr)
        return ERROR_MEMORY;

    list->arr = tmp.arr;

    return EXIT_SUCCESS;
}

int allocate_sparse_matrix(sparse_matrix_t *matrix)
{
    sparse_matrix_t tmp;

    tmp.a = calloc(matrix->unzero_size, sizeof(int));

    tmp.ia = calloc(matrix->unzero_size, sizeof(int));

    tmp.ja = calloc(matrix->y_size + 1, sizeof(int));

    if (!(tmp.a) || !(tmp.ja) || !(tmp.ia))
        return ERROR_MEMORY;

    matrix->a = tmp.a;
    matrix->ia = tmp.ia;
    matrix->ja = tmp.ja;

    return EXIT_SUCCESS;
}