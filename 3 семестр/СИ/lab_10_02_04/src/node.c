#include "node.h"

node_t *node_create(int num, int power)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
    
    node->num = num;
    node->power = power;
    node->next = NULL;

    return node;
}