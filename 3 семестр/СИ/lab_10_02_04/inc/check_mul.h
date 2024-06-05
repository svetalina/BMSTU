#ifndef CHECK_MUL_H
#define CHECK_MUL_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"

node_t *node_create(int num, int power);
node_t *list_add_front(node_t *head, node_t *node);
void list_free(node_t *head);

void list_mul(node_t *head_1, node_t *head_2, node_t **head_res);

int comparison_of_lists(node_t *head_a, node_t *head_b);
void check_mul(node_t *head_a, node_t *head_b, node_t *head_res);
Suite *mul_suite(Suite *s);

#endif
