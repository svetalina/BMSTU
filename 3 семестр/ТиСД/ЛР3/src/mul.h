#ifndef __MUL_H__
#define __MUL_H__

#include "struct.h"

void mul_std(std_matrix_t matrix, list_t list, list_t *result);
void mul_sparse(sparse_matrix_t matrix, list_t list, list_t *result);

#endif