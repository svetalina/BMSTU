#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <stdio.h>

#define SIZE 100

void init_data(int m[SIZE][SIZE], int n,  int a, int d);
void dijkstra(int m[SIZE][SIZE], int w[SIZE], int v[SIZE], int n);

#endif 