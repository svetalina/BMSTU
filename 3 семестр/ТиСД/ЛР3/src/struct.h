#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct
{
    int **matrix;
    int x_size;
    int y_size;
    int unzero_size;
} std_matrix_t;

typedef struct 
{
    int *a;
    int *ia;
    int *ja;
    int x_size;
    int y_size;
    int unzero_size;
} sparse_matrix_t;

typedef struct
{
    int *arr;
    int size;
} list_t;

#endif