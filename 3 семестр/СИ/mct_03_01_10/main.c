#include "matrix.h"
#include "matrices.h"

#define ERROR_MEMORY 1

int main(void)
{
    int num;
	scanf("%d ", &num);	
	
    matrix_t *array = malloc(num * sizeof(matrix_t));
    if (!array)
        return ERROR_MEMORY;
    
    array = matrices_read(array, num);
	
	matrices_delete(array, num, 2);
	matrices_delete(array, num, 5);
	
	return EXIT_SUCCESS;
}