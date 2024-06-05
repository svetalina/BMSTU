#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef struct year
{
    int *array;
    int size;
} year_t;

#endif