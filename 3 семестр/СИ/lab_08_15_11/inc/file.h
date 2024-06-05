#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "structure.h"
 
int file_read_sizes(FILE *f, matrix_t *const mtr);
int file_read_value(FILE *f, matrix_t *const mtr);
void file_print_result(FILE *f, matrix_t *const res);

#endif