#include <stdio.h>
#include <stdlib.h>

#include "array.h"

void create_array(int *array, int array_size)
{
	for (int i = 0; i < array_size; i++) 
		array[i] = rand() % 1000;
}

void print_array(int *array, int array_size)
{
	for (int i = 0; i < array_size; i++) 
		printf("%d ", array[i]);
}

void sort_array(void)
{	
	int array_size = 10;
	int array[10];
	
	void (*func[3])(int *array, int array_size) = {bucket_sort, heap_sort, bead_sort};
	void *inscription[3] = 
	{"Блочная сортировка:", "Пирамидальная сортировка:", "Бисерная сортировка:"};
	
	for (int i = 0; i < 3; i++)
	{
		printf("\n%s\n", inscription[i]);
		
		create_array(array, array_size);
		
		puts("Созданный массив:");
		print_array(array, array_size);
		puts("");
		
		func[i](array, array_size);
		
		puts("Отсортированный массив:");
		print_array(array, array_size);
		puts("");
	}
}