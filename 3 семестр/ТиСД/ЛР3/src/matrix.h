#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "memory.h"
#include "list.h"
#include "time.h"
#include "print.h"

#define ERROR_X_POS 3
#define ERROROR_READ_TYPE 4
#define ERROR_INPUT_SIZES 5
#define ERROR_VALUE_SIZES 6
#define ERROR_UNZERO_SIZE 7

#define r "\x1b[31m"
#define w "\x1b[0m"
#define g "\x1b[32m"
#define m "\x1b[35m"

int read_matrix(std_matrix_t *matrix, int unzero_size);
void random_matrix(std_matrix_t *matrix, int unzero_size);
int create_std_matrix(std_matrix_t *matrix, list_t *list);
int create_sparse_matrix(std_matrix_t std_matrix, sparse_matrix_t *matrix);

#endif