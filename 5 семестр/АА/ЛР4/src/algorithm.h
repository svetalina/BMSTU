#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "add_func.h"

void do_algorithm(int action);

void dijkstra_multi(int a[SIZE][SIZE], int *d, int *v);

void dijkstra(int a[SIZE][SIZE], int *d, int *v);

#define COUNT_THR 4

typedef struct{
	int (*a)[SIZE];
	int* d;
	int min;
	int minindex;
	int i;
} pthrData;

#endif