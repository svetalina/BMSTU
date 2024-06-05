#ifndef CHECK_APPEND_H
#define CHECK_APPEND_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structures.h"

node_t *create_node(void *num);
node_t *list_add_front(node_t *head, void *num);
int fill_list(node_t **head, year_t *array);
void free_list(node_t *head);

void append(node_t **head_a, node_t **head_b);

int comparison_of_lists(node_t *head_a, node_t *head_b);
Suite *append_suite(Suite *s);

#endif
