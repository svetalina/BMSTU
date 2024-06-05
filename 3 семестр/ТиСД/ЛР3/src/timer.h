#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


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

#define r "\x1b[31m"
#define w "\x1b[0m"
#define g "\x1b[32m"
#define m "\x1b[35m"

#define ERROR_ELEMENT 1
#define ERROR_Y_POS 2
#define ERROR_X_POS 3
#define ERROROR_READ_TYPE 4
#define ERROR_INPUT_SIZES 5
#define ERROR_VALUE_SIZES 6
#define ERROR_UNZERO_SIZE 7
#define ERROR_MEMORY 8
#define GHZ 1500000000

int read_list(list_t *list, int unzero_size);
void random_list(list_t *list, int unzero_size);
int read_matrix(std_matrix_t *matrix, int unzero_size);
void random_matrix(std_matrix_t *matrix, int unzero_size);
int create_std_matrix(std_matrix_t *matrix, list_t *list);
int create_sparse_matrix(std_matrix_t std_matrix, sparse_matrix_t *matrix);
void free_std_matrix(std_matrix_t matrix);
void free_list(list_t list);
void free_sparse_matrix(sparse_matrix_t matrix);
void free_all(std_matrix_t std_matrix, sparse_matrix_t sparse_matrix, list_t list);
int allocate_std_matrix(std_matrix_t *matrix);
int allocate_list(list_t *list);
int allocate_sparse_matrix(sparse_matrix_t *matrix);
void mul_std(std_matrix_t matrix, list_t list, list_t *result);
void mul_sparse(sparse_matrix_t matrix, list_t list, list_t *result);
uint64_t tick(void);