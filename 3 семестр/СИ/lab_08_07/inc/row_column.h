#ifndef ROW_COLUMN_H
#define ROW_COLUMN_H

#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "errors.h"

void row_delete(matrix_t *const matrix, int pos);
void column_delete(matrix_t *const matrix, int pos);
int row_change_memory(matrix_t *const matrix, const int size_diff);
int column_change_memory(matrix_t *const matrix, const int size_diff);
int row_find_max(matrix_t *const matrix, int pos);
int column_count_geometric_mean(matrix_t *const matrix, int pos);

#endif