#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "algorithm.h"

#define COUNT 50

#define MICRO 1000000


LARGE_INTEGER frequency;
LARGE_INTEGER t1,t2;
double elapsedTime;

void TIMER_INIT()
{
    QueryPerformanceFrequency(&frequency);
}

void TIMER_START()
{
	QueryPerformanceCounter(&t1);
}

double TIMER_STOP()
{
    QueryPerformanceCounter(&t2); 
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart/COUNT*MICRO;
	
	return elapsedTime;
}


void count_time()
{
	double time = 0;
	TIMER_INIT();
	
	int a[SIZE][SIZE];
	int d[SIZE];
	int v[SIZE];
	
	void (*func[2])(int a[SIZE][SIZE], int *d, int *v) = {dijkstra, dijkstra_multi,};
	void *inscription[3] = 
	{"Дейкстра", "Дейкстра многопоточный"};
	
	for (int j = 0; j < 2; j++)
	{
		printf("%s для %d элементов: ", inscription[j], SIZE);
		for (int k = 0; k < COUNT; k++)
		{
			init_data(a, d, v);
			
			TIMER_START();
				func[j](a, d, v);
			time += TIMER_STOP();
		}
		printf("%lf\n", time);
		puts("");
	}
}
