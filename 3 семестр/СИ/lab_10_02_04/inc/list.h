#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

node_t *list_add_front(node_t *head, node_t *node);
node_t *list_add_end(node_t *head, node_t *node);
void list_free(node_t *head);
void list_print(node_t *head);
void list_sqr(node_t **head);
void list_mul(node_t *head_1, node_t *head_2, node_t **head_res);
int list_delete_equal_num(node_t *head_1, node_t *head_2);

#endif