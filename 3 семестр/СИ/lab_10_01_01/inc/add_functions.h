#ifndef ADD_FUNCTIONS_H
#define ADD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define ERROR_MEMORY 2

node_t *list_add_front(node_t *head, void *num);
int fill_list(node_t **head, year_t *array);
void free_list(node_t *head);
int comparator(const void *var1, const void *var2);
void insert_elem(node_t *prev_elem, node_t *next_elem, node_t *element, node_t **head);

#endif