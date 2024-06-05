#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

matrix_t* matrices_read(matrix_t* array, int num);
void matrices_delete(matrix_t* array, int num, int deletel);
void matrices_print(matrix_t* array, int num);

#endif