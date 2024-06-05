#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "algorithm.h"

void dijkstra(int a[SIZE][SIZE], int *d, int *v)
{
    int temp, minindex, min;
	int begin_index = 0;
    
	d[begin_index] = 0;
  
	do {
		minindex = min = INT_MAX;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != INT_MAX)
		{
			for (int i = 0; i < SIZE; i++)
				if (a[minindex][i] > 0)
					d[i] = get_min(2, d[i], min + a[minindex][i]);
			v[minindex] = 0;
		}
	} while (minindex < INT_MAX);
}

void* threadFunc(void *thread_data)
{
	pthrData *data = (pthrData*) thread_data;
	
	if (data->a[data->minindex][data->i] > 0)
		data->d[data->i] = get_min(2, data->d[data->i], data->min + data->a[data->minindex][data->i]);
	
	return NULL;
}

void dijkstra_multi(int a[SIZE][SIZE], int *d, int *v)
{
	pthread_t* threads = (pthread_t*) malloc(COUNT_THR * sizeof(pthread_t));
	pthrData* threadData = (pthrData*) malloc(COUNT_THR * sizeof(pthrData));

	
    int temp, minindex, min;
	int begin_index = 0;
    
	d[begin_index] = 0;
  
	do {
		minindex = min = INT_MAX;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != INT_MAX)
		{	
			for (int i = 0; i < SIZE; i += COUNT_THR)
			{		
				for (int j = 0; j < COUNT_THR; j++)
				{
					threadData[j].a = a;
					threadData[j].d = d;
					threadData[j].min = min;
					threadData[j].minindex = minindex;
					threadData[j].i = i + j;
					
					pthread_create(&(threads[j]), NULL, threadFunc, &threadData[j]);
				}
				for(int j = 0; j < COUNT_THR; j++)
					pthread_join(threads[j], NULL);
			}
			v[minindex] = 0;
		}
	} while (minindex < INT_MAX);
}

void do_algorithm(int action)
{
	int a[SIZE][SIZE];
	int d[SIZE];
	int v[SIZE];
  
	init_data(a, d, v);
  
	printf("\nМатрица смежностей: \n");
	print_matrix(a);
  
	if(action == 1)
		dijkstra(a, d, v);
	else
		dijkstra_multi(a, d, v);
    
	printf("\nКратчайшие расстояния до вершин: \n");
	print_array(d);
}