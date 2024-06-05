#ifndef CHECK_SQR_H
#define CHECK_SQR_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "structure.h"

node_t *node_create(int num, int power);
node_t *list_add_front(node_t *head, node_t *node);
void list_free(node_t *head);

void list_sqr(node_t **head);

int comparison_of_lists(node_t *head_a, node_t *head_b);
void check_sqr(node_t *head);
Suite *sqr_suite(Suite *s);

#endif
