#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct node node_t;
struct node
{
    int num;
    int power;
    node_t *next;
};

#endif