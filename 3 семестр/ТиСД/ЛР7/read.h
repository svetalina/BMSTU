#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define r "\x1b[31m"
#define g "\x1b[32m"
#define w "\x1b[0m"

#define ERROR_SYMBOLS 2
#define ERROR_VALUE 3
#define ERROR_EQUAL_VERTEX 5

int read_type_filling(int *type_filling);
int read_size_graph(FILE *f, int *size, int type_filling);
int read_graph(FILE *f, graph_t graph, int type_filling);
int read_vertexs(int *start_vertex, int *end_vertex, graph_t graph);

#endif