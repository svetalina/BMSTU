#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "array.h"

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


void create_array_inc(int *array, int array_size)
{
	array[0] = rand() % 10;
	for (int i = 1; i < array_size; i++) 
		array[i] = array[i - 1] + rand() % 10;
}

void create_array_dec(int *array, int array_size)
{
	array[array_size - 1] = rand() % 10000;
	for (int i = array_size - 2; i >= 0; i--) 
		array[i] = array[i + 1] - rand() % 10;
}

void count_time()
{
	double time = 0;
	TIMER_INIT();
	
	int array_size[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
	int array[1000];
	
	void (*func[3])(int *array, int array_size) = {bucket_sort, heap_sort, bead_sort};
	void *inscription[3] = 
	{"Блочная сортировка", "Пирамидальная сортировка", "Бисерная сортировка"};
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%s для %d элементов: ", inscription[j], array_size[i]);
			for (int k = 0; k < COUNT; k++)
			{
				create_array_dec(array, array_size[i]);
				TIMER_START();
				func[j](array, array_size[i]);
				time += TIMER_STOP();
			}
			printf("%lf\n", time);
		}
		puts("");
	}
}
