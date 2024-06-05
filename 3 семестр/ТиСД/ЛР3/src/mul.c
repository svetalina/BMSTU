#include <stdio.h>
#include "mul.h"

void mul_std(std_matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    int ind = 0, num;
    for (int j = 0; j < matrix.y_size; j++)
    {
        num = 0;

        for (int i = 0; i < matrix.x_size; i++)
            num += matrix.matrix[i][j] * list.arr[i];

        tmp.arr[ind++] = num;
    }

    *result = tmp;
}

void mul_sparse(sparse_matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    for (int i = 1; i <= matrix.y_size + 1; i++)  
        for (int j = matrix.ja[i - 1]; j < matrix.ja[i]; j++)
            tmp.arr[i - 1] += matrix.a[j] * list.arr[matrix.ia[j]];

    *result = tmp;
}