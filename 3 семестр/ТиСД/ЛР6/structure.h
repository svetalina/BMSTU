#ifndef STRUCTURE_H
#define STRUCTURE_H

struct tree_node_t
{
    int value;
    unsigned char height;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

typedef struct
{
    int key;
    int status;
} node_hash_t;

struct hash_t
{
    node_hash_t *array;
    int size;
};

#endif