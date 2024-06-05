#include "heap_sort.h"

void swap(int *a, int *b)
{
    int tmp;
    
    tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify(int *arr, int array_size, int i)
{
    int largest = i;   

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < array_size && arr[l] > arr[largest])
        largest = l;

    if (r < array_size && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(&(arr[i]), &(arr[largest]));
        heapify(arr, array_size, largest);
    }
}

void heap_sort(int *arr, int array_size)
{
    for (int i = array_size / 2 - 1; i >= 0; i--)
        heapify(arr, array_size, i);

    for (int i = array_size - 1; i >= 0; i--)
    {
        swap(&(arr[0]), &(arr[i]));
        heapify(arr, i, 0);
    }
}
