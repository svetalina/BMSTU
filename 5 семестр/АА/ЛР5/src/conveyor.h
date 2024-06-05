#ifndef _CONVEYOR_H_
#define _CONVEYOR_H_

#include <cstdio>

#include "dijkstra.h"

#define get_time(time) __asm__ __volatile__("rdtsc" :"=A"(time))

#define THREADS_COUNT 3

typedef struct
{
	int n, a, d;
    int m[SIZE][SIZE];
	int w[SIZE];
	int v[SIZE];
	FILE *f;
} request_t;

typedef struct request_state
{
    bool stage_1;
    bool stage_2;
    bool stage_3;
} request_state_t;

void linear_processing(int num_of_requests, int n, int a, int d);
void conveyor_processing(int num_of_requests, int n, int a, int d);

#endif
