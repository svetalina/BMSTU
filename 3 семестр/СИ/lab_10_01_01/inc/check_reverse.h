#ifndef CHECK_REVERSE_H
#define CHECK_rREVERSE_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structures.h"

node_t *create_node(void *num);
node_t *list_add_front(node_t *head, void *num);
int fill_list(node_t **head, year_t *array);
void free_list(node_t *head);

void *pop_front(node_t **head);
node_t *reverse(node_t *head);

int comparison_of_lists(node_t *head_a, node_t *head_b);
Suite *reverse_suite(Suite *s);

#endif
