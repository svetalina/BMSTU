#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include "struct.h"
#include "memory.h"
#include "time.h"

#define GHZ 1500000000

#define r "\x1b[31m"
#define w "\x1b[0m"
#define g "\x1b[32m"
#define m "\x1b[35m"

void print_info();
void print_std_matrix(std_matrix_t matrix);
void print_sparse_matrix(sparse_matrix_t matrix);
void print_std_list(list_t list);
void print_sparse_list(list_t list);
void print_result(sparse_matrix_t sparse_matrix, std_matrix_t std_matrix, int64_t time1, int64_t time2);

#endif