#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

#define r "\x1b[31m"
#define w "\x1b[0m"
#define y "\x1b[33m"
#define c "\x1b[36m"
#define g "\x1b[32m"


uint64_t tick(void);
int compare_turns(void);


#define ERROR_MEMORY 7

int add_to_array(turn_array_t *turn_array, int add_num);
int add_to_list(turn_array_t *turn_array, int num_add, turn_list_t *list);
void fill_to_array_randomly(turn_array_t *turn_array, int add_num);
void remove_from_array(turn_array_t *turn_array, int remove_num);
int fill_to_list_randomly(turn_list_t *list, int remove_num);
void remove_from_list(turn_list_t *list, int remove_num);
int add_addresses(array_freed_areas_t *array, int remove_num, turn_list_t *list);
void free_turn_list(turn_list_t *list);


#define HZ 2300000000

void print_general_menu(void);
void print_menu(void);
void print_result(int64_t start, int64_t end);
void print_turn_array(turn_array_t *turn_array);
void print_turn_list(turn_list_t *list);
void print_freed_array(array_freed_areas_t *array);


#define ERROR_SYMBOLS 1
#define ERROR_GENERAL_ACTION 2
#define ERROR_MENU_ACTION 3
#define ERROR_OVERFLOW 4
#define ERROR_ADD_NUM 5
#define ERROR_EMPTY 6
#define ERROR_NUM_REMOVE 5

int read_general_action(int *general_action);
int read_menu_action(int *menu_action);
int read_add_num(int *add_num, int size);
int read_new_elem(int *new_elem);
int read_num_remove(int *num_remove, int size);

#define UNIT_OF_TIME 10000

#define MIN_T1 0  
#define MAX_T1 5

#define MIN_T2 0  
#define MAX_T2 4 

#define MIN_T3 0  
#define MAX_T3 4 

int solution_problem(void);

#endif