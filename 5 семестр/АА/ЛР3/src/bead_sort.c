#include <stdlib.h>

#include "bead_sort.h"

void bead_sort(int *array, int array_size)
{
    int max = array[0]; 
	for (int i = 1; i < array_size; i++)
		if (array[i] > max) 
			max = array[i];
    
    unsigned char *beads = calloc(1, max * array_size);
	for (int i = 0; i < array_size; i++) 
		for (int j = 0; j < array[i]; j++)
			beads[i * max + j] = 1;
    
    for (int j = 0; j < max; j++) 
	{
	    int sum = 0;
		for (int i = 0; i < array_size; i++)
		{
			sum += beads[i * max + j];
			beads[i * max + j] = 0;
		}
		
		for (int i = array_size - sum; i < array_size; i++)
		    beads[i * max + j] = 1;
	}
	
	int indx;
	for (int i = 0; i < array_size; i++) {
		for (indx = 0; indx < max && beads[i * max + indx]; indx++);
		array[i] = indx;
	}
	free(beads);
}
