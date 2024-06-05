#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "structure.h"
#include "print.h"

#define r "\x1b[31m"
#define y "\x1b[33m"
#define g "\x1b[32m"
#define c "\x1b[36m"
#define w "\x1b[0m"

#define ERROR_MEMORY 4
#define ERROR_SYMBOLS 5

extern int rotate;
extern int deleted;

typedef struct tree_node_t *(*ptr_action_second_t)(struct tree_node_t *);

int fill_tree(FILE *f, struct tree_node_t **root, int *size);
struct tree_node_t *copy_node(struct tree_node_t *root);
struct tree_node_t *btree_balance_post(struct tree_node_t *tree, ptr_action_second_t f);
struct tree_node_t *balance(struct tree_node_t *node);
void node_free(struct tree_node_t *node, void *ptr);
void btree_free_post(struct tree_node_t *tree, ptr_action_first_t f, void *arg);
struct tree_node_t *remove_el(struct tree_node_t *tree, int el, int flag);

#endif