#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

#define ERROR_MEMORY 8

void free_std_matrix(std_matrix_t matrix);
void free_list(list_t list);
void free_sparse_matrix(sparse_matrix_t matrix);
void free_all(std_matrix_t std_matrix, sparse_matrix_t sparse_matrix, list_t list);
int allocate_std_matrix(std_matrix_t *matrix);
int allocate_list(list_t *list);
int allocate_sparse_matrix(sparse_matrix_t *matrix);

#endif