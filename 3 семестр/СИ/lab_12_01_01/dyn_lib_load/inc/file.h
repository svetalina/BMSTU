#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN 2
#define ERROR_SYMBOL 3
#define ERROR_EMPTY_FILE 4

int file_count_numbers(int *const counter_num, FILE *const f);
int file_write(int *pb_array, int *pe_array, FILE *f);

#endif
