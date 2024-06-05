#ifndef LAB_FUNCTIONS_H
#define LAB_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void append(node_t **head_a, node_t **head_b);
void remove_duplicates(node_t **head,
int (*comparator)(const void*, const void*));
node_t *sort(node_t *head, int (*comparator)(const void*, const void*));
void *pop_front(node_t **head);
node_t *reverse(node_t *head);

#endif