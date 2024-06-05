#ifndef READ_PRINT_H
#define READ_PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define ERROR_OPEN_FILE 1
#define ERROR_MEMORY 2
#define ERROR_READING 3

int read_years(const char *file_name, year_t *array);
void print_list(node_t *head);

#endif