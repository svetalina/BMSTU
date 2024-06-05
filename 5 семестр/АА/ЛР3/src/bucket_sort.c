#include "bucket_sort.h"

void bucket_sort(int *array, int array_size) 
{
    int bucket[10][array_size + 1];

    for(int x = 0; x < 10; x++)
		bucket[x][array_size] = 0;

    for(int digit = 1; digit <= 1000000000; digit *= 10)
	{
        for(int i = 0; i < array_size; i++)
		{
            int dig = (array[i] / digit) % 10;
            bucket[dig][bucket[dig][array_size]++] = array[i];
        }

        int idx = 0;
        for(int x = 0; x < 10; x++)
		{
            for(int y = 0; y < bucket[x][array_size]; y++)
                array[idx++] = bucket[x][y];
            bucket[x][array_size] = 0;
        }
    }
}