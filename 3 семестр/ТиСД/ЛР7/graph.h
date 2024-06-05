#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define r "\x1b[31m"
#define g "\x1b[32m"
#define w "\x1b[0m"

#define ERROR_GRAPH 4

graph_t create_graph(int size);
int deijkstra(graph_t graph, int start_vertex, int end_vertex);

#endif