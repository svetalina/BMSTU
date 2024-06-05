#include "matrix.h"
#include "file.h"

double **allocate_matrix(int const n, int const m)
{
    double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
        data[i] = (double*)((char*) data + n * sizeof(double*) +  i * m * sizeof(double));
    
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            data[i][j] = 0;
        
    return data;
}

int matrix_filling(char *const name, matrix_t *const mtr)
{
    int rc;
    FILE *f;
    
    if ((f = fopen(name, "r")) == NULL)
        return ERROR_FILE_OPEN;
    
    if ((rc = file_read_sizes(f, mtr)))
        goto end;
    
    if (!(mtr->mtr = allocate_matrix(mtr->i_size, mtr->j_size)))
    {
        rc = ERROR_MEMORY;
        goto end;
    }
    
    if ((rc = file_read_value(f, mtr)))
    {
        free(mtr->mtr);
        goto end;
    }
    
    fclose(f);
    return EXIT_SUCCESS;
    
    end:
        fclose(f);
    return rc;
}

int res_matrix_create(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, int const key)
{
    int rc;
    
    res->i_size = mtr_1->i_size;
    res->j_size = mtr_2->j_size;
    
    if ((!key && (mtr_1->i_size != mtr_2->i_size || mtr_1->j_size != mtr_2->j_size)) ||
        (key && (mtr_1->j_size != mtr_2->i_size)))
    {
        rc = ERROR_MATCH_SIZES;
        goto end;
    }
    
    if (!(res->mtr = allocate_matrix(res->i_size, res->j_size)))
    {
        rc = ERROR_MEMORY;
        goto end;
    }
    
    return EXIT_SUCCESS;
    
    end:
        free(mtr_1->mtr);
    free(mtr_2->mtr);
    return rc;
}

int identity_matrix_create(matrix_t *mtr, matrix_t *res)
{   
    int rc;

    res->i_size = mtr->i_size;
    res->j_size = mtr->j_size;
    
    if (mtr->i_size != mtr->j_size)
    {
        rc = ERROR_MATCH_SIZES;
        goto end;
    }
    if (!(res->mtr = allocate_matrix(res->i_size, res->j_size)))
    {
        rc = ERROR_MEMORY;
        goto end;
    }
    
    for (size_t i = 0; i < res->i_size; i++)
        res->mtr[i][i] = 1.0;
    
    return EXIT_SUCCESS;
    
    end:
        free(mtr->mtr);
    return rc;
}

void matrix_addition(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res)
{
    for (size_t i = 0; i < mtr_1->i_size; i++)
        for (size_t j = 0; j < mtr_1->j_size; j++)
            res->mtr[i][j] = mtr_1->mtr[i][j] + mtr_2->mtr[i][j];
}

void matrix_multiplication(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res)
{
    for (size_t i = 0; i < mtr_1->i_size; i++)
        for (size_t j = 0; j < mtr_2->j_size; j++)
            for (size_t k = 0; k < mtr_1->j_size; k++)
                res->mtr[i][j] += mtr_1->mtr[i][k] * mtr_2->mtr[k][j];
}

int matrix_inversion_unzero_row(matrix_t *const mtr, int ind, double *base)
{
    int flag = 0;
    double *buf;
    
    for (int i = ind; i < mtr->i_size; i++)
    {
        if (mtr->mtr[i][ind] != 0)
        {
            *base = mtr->mtr[i][ind];
            
            buf = mtr->mtr[ind];
            mtr->mtr[ind] = mtr->mtr[i]; 
            mtr->mtr[i] = buf;
            
            flag = 1;
            break;
        }
    }
    
    if (!flag)
        return ERROR_DEGENERATE_MATRIX;
    
    return EXIT_SUCCESS;
}

int matrix_inversion(matrix_t *const mtr, matrix_t *const res)
{
    int rc;
    
    double tmp;
 
    for (int k = 0; k < mtr->i_size; k++)
    {   
        if ((rc = matrix_inversion_unzero_row(mtr, k, &tmp)))
        {
            free(mtr->mtr);
            free(res->mtr);
            return rc;
        }
        
        for (int j = 0; j < mtr->j_size; j++)
        {
            mtr->mtr[k][j] /= tmp;
            res->mtr[k][j] /= tmp;
        }
        
        for (int i = k + 1; i < mtr->i_size; i++)
        {
            tmp = mtr->mtr[i][k];
            for (int j = 0; j < mtr->i_size; j++)
            {
                mtr->mtr[i][j] -= mtr->mtr[k][j] * tmp;
                res->mtr[i][j] -= res->mtr[k][j] * tmp;
            }
        }
    }
 
    for (int k = mtr->i_size - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            tmp = mtr->mtr[i][k];
            for (int j = 0; j < mtr->i_size; j++)
            {
                mtr->mtr[i][j] -= mtr->mtr[k][j] * tmp;
                res->mtr[i][j] -= res->mtr[k][j] * tmp;
            }
        }
    }
   
    return EXIT_SUCCESS;
}

int matrix_print_main(char *const name, matrix_t *const res)
{
    int rc;
    
    FILE *f;
    
    if ((f = fopen(name, "w")) == NULL)
    {
        rc = ERROR_FILE_OPEN;
        goto end;
    }
    
    file_print_result(f, res);
    free(res->mtr);
    
    fclose(f);
    return EXIT_SUCCESS;
    
    end:
        free(res->mtr);
    return rc;
}
