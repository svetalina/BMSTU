#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "structures.h"

#define r "\x1b[31m"
#define y "\x1b[33m"
#define w "\x1b[0m"

#define green "\x1b[42m"
#define red "\x1b[41m"

#define ERROR_SYMBOLS 1
#define ERROR_STACK_TYPE 2
#define ERROR_ACTION_TYPE 3
#define ERROR_STACK_OVERLOW 4
#define ERROR_NUM_ADD 5
#define ERROR_STACK_EMPTY 6
#define ERROR_NUM_REMOVE 7
#define ERROR_MEMORY 8

#define HZ 1500000000

void print_stack_array(stack_array_t *stack_array);
void print_stack_list(el_stack_list_t **el_stack_list);
void print_array(array_free_areas_t *array);

int read_stack_type(int *stack_type);
int read_action_type(int *action_type);
int read_new_el(char *new_elem);
int read_num_to_add_stack_array(int *num_add, int size);
int read_num_to_remove_stack_array(int *num_remove, int size);
int read_num_to_add_stack_list(int *num_add, el_stack_list_t *el_stack_list);
int read_num_to_remove_stack_list(int *num_remove, el_stack_list_t *elem_stack_list);

int stack_array(void);
int add_stack_array(stack_array_t *stack_array, int num_add);
void add_stack_array_random(stack_array_t *stack_array, int num_add);
void remove_stack_array(stack_array_t *stack_array, int num_remove);
void check_brackets_array(stack_array_t *stack_array);

int stack_list(void);
void free_stack_list(el_stack_list_t **el_stack_list);
int add_stack_list(el_stack_list_t **el_stack_list, int num_add);
int add_stack_list_random(el_stack_list_t **el_stack_list, int num_add);
int add_addresses(array_free_areas_t *array, int num_remove, el_stack_list_t *el_stack_list);
void remove_stack_list(el_stack_list_t **el_stack_list, int num_remove);
void check_brackets_list(el_stack_list_t **el_stack_list);

int comparison_stacks(void);
uint64_t tick(void);
void print_result(int64_t start, int64_t end);

#endif