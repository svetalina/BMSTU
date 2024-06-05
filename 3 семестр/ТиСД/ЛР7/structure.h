#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct
{
	int length;
	int price;
}road_t;

typedef struct
{
    int size;
    road_t **matrix;
	char *path;
} graph_t;

#endif