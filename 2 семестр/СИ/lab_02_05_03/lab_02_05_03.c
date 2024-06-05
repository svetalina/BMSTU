#include <stdio.h>

#define NEG -1000
#define NOT_SIZE -2
#define OK 0

#define MAX_SIZE 10
#define MIN_CONST 1000
#define INPUT_OK 1

int check_size(void)
{
    int size_func;
    
    if (scanf("%d", &size_func) != INPUT_OK)
    {
        printf("Input size error");
        return NOT_SIZE;
    }

    if (size_func > MAX_SIZE || size_func <= 1)
    {
        printf("Input size error");
        return NOT_SIZE;
    }

    return size_func;
}

int composition(const int number_1, const int number_2, int min)
{
    if (number_1 * number_2 < min)
    {
        min = number_1 * number_2;
    }

    return min;
}

int check_array(int *pointer_array, const int size_func)
{
    int min = MIN_CONST, count = 1;
    
    if (scanf("%d", pointer_array) != INPUT_OK)
    {
        printf("Input array error");
        return NEG;
    }
	
    pointer_array += 1;

    while (count != size_func)
    {
        if (scanf("%d", pointer_array) != INPUT_OK)
        {
            printf("Input array error");
            return NEG;
        }
		
        min = composition(*pointer_array, *(pointer_array - 1), min);
        pointer_array += 1;
        count++;
    }
    
    return min;
}

int main(void)
{
    int size, min;
    int array[MAX_SIZE] = { 0 };
    int *pointer_array;

    pointer_array = &array[0];

    size = check_size();
    
    if (size < 0)
    {
        return NOT_SIZE;
    }

    min = check_array(pointer_array, size);
    
    if (min == NEG)
    {
        return min;
    }

    printf("%d", min);
    
    return OK;
}
