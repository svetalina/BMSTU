#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "structure.h"
#include "time.h"

#define r "\x1b[31m"
#define y "\x1b[33m"
#define g "\x1b[32m"
#define c "\x1b[36m"
#define w "\x1b[0m"

#define BUSY 1
#define DELETED 2

#define ERROR_MEMORY 4
#define ERROR_SYMBOLS 5

typedef int (*hash_func_t)(int, int);
int hash_func_1(int value, int size);
int hash_func_2(int value, int size);

int fill_table(FILE *f, struct hash_t *hash_table, int size, hash_func_t hash_func);
int delete_from_table(FILE *f, struct hash_t *hash_table, int key);

#endif
