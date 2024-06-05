#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

#define ERROR_ELEMENT 1
#define ERROR_Y_POS 2

#define r "\x1b[31m"
#define w "\x1b[0m"
#define g "\x1b[32m"
#define m "\x1b[35m"

int read_list(list_t *list, int unzero_size);
void random_list(list_t *list, int unzero_size);

#endif