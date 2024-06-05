#ifndef CHECK_DIV_H
#define CHECK_DIV_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"

node_t *node_create(int num, int power);
node_t *list_add_front(node_t *head, node_t *node);
void list_free(node_t *head);

int list_delete_equal_num(node_t *head_1, node_t *head_2);

void check_div(node_t *head_a, node_t *head_b, int res);
Suite *div_suite(Suite *s);

#endif
