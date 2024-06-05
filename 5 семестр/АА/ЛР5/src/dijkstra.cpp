#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#include "dijkstra.h"

void init_data(int m[SIZE][SIZE], int n,  int a, int d)
{	
	for (int i = 0; i < n; i++)
		
	{      
		m[i][i] = 0;
		for (int j = i + 1; j < n; j++)
			m[i][j] = m[j][i] = (a - d*a) + rand() % (2*d*a);
	}
}

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

void dijkstra(int m[SIZE][SIZE], int w[SIZE], int v[SIZE], int n)
{
	for (int i = 0; i < n; i++)
	{
		w[i] = INT_MAX;
		v[i] = 1;
	}
	
    int minindex, min;
	int begin_index = 0;
    
	w[begin_index] = 0;
  
	do {
		minindex = min = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			if ((v[i] == 1) && (w[i] < min))
			{
				min = w[i];
				minindex = i;
			}
		}

		if (minindex != INT_MAX)
		{
			for (int i = 0; i < n; i++)
				if (m[minindex][i] > 0)
					w[i] = get_min(2, w[i], min + m[minindex][i]);
			v[minindex] = 0;
		}
	} while (minindex < INT_MAX);
}
