#ifndef CHECK_SORT_H
#define CHECK_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structures.h"

node_t *create_node(void *num);
node_t *list_add_front(node_t *head, void *num);
int fill_list(node_t **head, year_t *array);
void free_list(node_t *head);

int comparator(const void *var1, const void *var2);
void sorted_insert(node_t **head, node_t *element,
int (*comparator)(const void*, const void*));
node_t *sort(node_t *head, int (*comparator)(const void*, const void*));

int comparison_of_lists(node_t *head_a, node_t *head_b);
Suite *sort_suite(Suite *s);

#endif
