#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define r "\x1b[31m"
#define g "\x1b[32m"
#define w "\x1b[0m"

void print_graph(graph_t graph);
void print_matrix(graph_t graph);
void print_path(graph_t graph);

#endif