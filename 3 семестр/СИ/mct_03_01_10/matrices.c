#include "matrix.h"
#include "matrices.h"

matrix_t* matrices_read(matrix_t* array, int num)
{ 
    for (int i = 0; i < num; i++)
    {
        read_matrix_size(&array[i]);
        array[i].matrix = allocate_matrix(array[i].rows, array[i].columns);
        read_matrix(&array[i]);
    }
	
	return array;
}

// void* comparator(void* matrix_1, void* matrix_2)
// {
    // return *(int*) matrix_1->min - *(int*) matrix_2->min;
// }

void matrices_sort(matrix_t* array, int num)
{
    for (int i = 0; i < num; i++)
        find_matrix_min(&array[i]);
	
    // qsort(array, num, sizeof(matrix_t), comparator);
}

void matrices_delete(matrix_t* array, int num, int deletel)
{
    for (int i = 0; i < num; i++)
    {
        if ((array[i].min) % deletel == 0)
		{
			free(array[i].matrix);
			num--;
		}
    }
	
	matrices_print(array, num); 
}

void matrices_print(matrix_t* array, int num)
{
    for (int i = 0; i < num; i++)
        print_matrix(&array[i]);
}