#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "structure.h"
#include "table.h"

#define r "\x1b[31m"
#define y "\x1b[33m"
#define g "\x1b[32m"
#define с "\x1b[36m"
#define w "\x1b[0m"

typedef void (*ptr_action_first_t)(struct tree_node_t *, void *);

void print_menu(void);
void print_tree(struct tree_node_t *root, int size, int flag);
void print_table(struct hash_t *hash_table, hash_func_t hash_func);

#endif
