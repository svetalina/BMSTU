#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_STACK_SIZE 1000

typedef struct stack_array
{
    char *ptr;
    int size;
} stack_array_t;

typedef struct el_stack_list
{
    char el;
    int num_el;
    struct el_stack_list *next;
} el_stack_list_t;

typedef struct array_free_areas
{
    el_stack_list_t **array;
    int size;
} array_free_areas_t;

#endif