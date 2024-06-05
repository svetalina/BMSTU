#ifndef CHECK_DECOMPOSITION_H
#define CHECK_DECOMPOSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"

#define ERROR_DECOMPOSOTION 3

node_t *node_create(int num, int power);
node_t *list_add_front(node_t *head, node_t *node);
void list_free(node_t *head);

int number_decomposion(node_t **head, int num);

int comparison_of_lists(node_t *head_a, node_t *head_b);
void check_decomposition(node_t *head, int num);
Suite *decomposition_suite(Suite *s);

#endif
