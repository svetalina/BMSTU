#include <stdio.h>

#include "multiply_matrix.h"
#include "matrix.h"

matrix_t *mul_matrix_def(matrix_t *mat_1, matrix_t *mat_2)
{
    matrix_t *res = create_matrix(mat_1->rows, mat_2->cols);
	
    for (int i = 0; i < res->rows; ++i)
        for (int j = 0; j < res->cols; ++j)
            for (int k = 0; k < mat_1->cols; ++k)
                (res->elements)[i][j] += (mat_1->elements)[i][k] * (mat_2->elements)[k][j];

    return res;
}

matrix_t *mul_matrix_vinograd(matrix_t *mat_1, matrix_t *mat_2)
{
    matrix_t *res = create_matrix(mat_1->rows, mat_2->cols);
    int *row_factor = calloc(mat_1->rows, sizeof(int));
    int *column_factor = calloc(mat_2->cols, sizeof(int));

    for (int i = 0; i < mat_1->rows; ++i)
        for (int j = 0; j < mat_1->cols / 2; ++j)
            row_factor[i] = row_factor[i] + (mat_1->elements)[i][2 * j] * (mat_1->elements)[i][2 * j + 1];

    for (int i = 0; i < mat_2->cols; ++i)
        for (int j = 0; j < mat_1->cols / 2; ++j)
            column_factor[i] = column_factor[i] + (mat_2->elements)[2 * j][i] * (mat_2->elements)[2 * j + 1][i];
	
    for (int i = 0; i < res->rows; ++i)
        for (int j = 0; j < res->cols; ++j) {
			(res->elements)[i][j] = -row_factor[i] - column_factor[j];
			for (int k = 0; k < mat_1->cols / 2; ++k)
                (res->elements)[i][j] = (res->elements)[i][j] +\
										((mat_1->elements)[i][2 * k] +\
										(mat_2->elements)[2 * k + 1][j]) * ((mat_1->elements)[i][2 * k + 1] +\
										(mat_2->elements)[2 * k][j]);
		}

    if (mat_1->cols % 2 != 0) {
        for (int i = 0; i < res->rows; ++i)
            for (int j = 0; j < res->cols; ++j)
                (res->elements)[i][j] = (res->elements)[i][j] +\
										(mat_1->elements)[i][mat_1->cols - 1] * (mat_2->elements)[mat_2->rows - 1][j];
    }

    free(row_factor);
    free(column_factor);

    return res;
}

matrix_t *mul_matrix_vinograd_opt(matrix_t *mat_1, matrix_t *mat_2)
{
    matrix_t *res = create_matrix(mat_1->rows, mat_2->cols);
    int *row_factor = calloc(mat_1->rows, sizeof(int));
    int *column_factor = calloc(mat_2->cols, sizeof(int));

    int eq_dim = mat_1->cols;
    int half_eq_dim = eq_dim >> 1;

    for (int i = 0; i < mat_1->rows; ++i)
        for (int j = 0; j < half_eq_dim; ++j)
            row_factor[i] += (mat_1->elements)[i][j << 1] * (mat_1->elements)[i][(j << 1) + 1];

    for (int i = 0; i < mat_2->cols; ++i)
        for (int j = 0; j < half_eq_dim; ++j)
            column_factor[i] += (mat_2->elements)[j << 1][i] * (mat_2->elements)[(j << 1) + 1][i];

    for (int i = 0; i < res->rows; ++i)
        for (int j = 0; j < res->cols; ++j) {
            (res->elements)[i][j] = -row_factor[i] - column_factor[j];
            for (int k = 0; k < half_eq_dim; ++k)
                (res->elements)[i][j] += ((mat_1->elements)[i][k << 1] +\
										 (mat_2->elements)[(k << 1) + 1][j]) * ((mat_1->elements)[i][(k << 1) + 1] +\
										 (mat_2->elements)[(k << 1)][j]);
        }

    if (eq_dim % 2 != 0) {
        for (int i = 0; i < res->rows; ++i)
            for (int j = 0; j < res->cols; ++j)
                (res->elements)[i][j] += (mat_1->elements)[i][mat_1->cols - 1] * (mat_2->elements)[mat_2->rows - 1][j];
    }

    free(row_factor);
    free(column_factor);

    return res;
}

int multiply_matrix(int action)
{
	int rc;
    
	matrix_t *mat_1, *mat_2;
    printf("--------------------Первая матрица--------------------\n");
    if ((rc = read_matrix(&mat_1)))
        return rc;
    printf("--------------------Вторая матрица--------------------\n");
    if ((rc = read_matrix(&mat_2))) {
        free_matrix(mat_1);
        return rc;
    }

    matrix_t *res;
    switch (action) {
        case 1:
            res = mul_matrix_def(mat_1, mat_2);
            break;
        case 2:
            res = mul_matrix_vinograd(mat_1, mat_2);
            break;
        case 3:
            res = mul_matrix_vinograd_opt(mat_1, mat_2);
            break;
        default:
            return -1;
    }

    printf("Result matrix:\n");
    print_matrix(res);

    free_matrix(res);

    return EXIT_SUCCESS;
}
