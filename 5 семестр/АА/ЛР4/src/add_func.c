#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>

#include "add_func.h"

int get_min(int n, ...)
{
	int el, res = INT_MAX;
    va_list factor;         
    va_start(factor, n);
    for(int i = 0; i < n; i++)
    {
		el = va_arg(factor, int);
        if (el < res)
			res = el;
    }
    va_end(factor); 
    return res;
}

void init_data(int a[SIZE][SIZE], int *d, int *v)
{
	srand(time(NULL));
	
	for (int i = 0; i < SIZE; i++)
	{
		d[i] = INT_MAX;
		v[i] = 1;
      
		a[i][i] = 0;
		for (int j = i + 1; j < SIZE; j++)
		a[i][j] = a[j][i] = rand() % 100;
	}
}

void print_matrix(int a[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		  printf("%5d ", a[i][j]);
		printf("\n");
	}
}

void print_array(int *d)
{
	for (int i = 0; i < SIZE; i++)
		printf("%5d ", d[i]);
}
