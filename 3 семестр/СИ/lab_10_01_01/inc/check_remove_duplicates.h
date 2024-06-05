#ifndef CHECK_REMOVE_DUPLICATES_H
#define CHECK_REMOVE_DUPLICATES_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structures.h"

node_t *create_node(void *num);
node_t *list_add_front(node_t *head, void *num);
int fill_list(node_t **head, year_t *array);
void free_list(node_t *head);

int comparator(const void *var1, const void *var2);
void remove_duplicates(node_t **head,
int (*comparator)(const void*, const void*));

int comparison_of_lists(node_t *head_a, node_t *head_b);
Suite *remove_duplicates_suite(Suite *s);

#endif
