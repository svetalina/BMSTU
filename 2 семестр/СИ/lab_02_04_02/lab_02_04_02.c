#include <stdio.h>

#define MAX_SIZE 11
#define INPUT_OK 1

#define SPECIAL 100
#define NOT_ARRAY -1
#define OK 0

void selection_sort(int *num, const int size)
{
    int min, temp;
    
    for (int i = 0; i < size - 1; i++)
    {
        min = i;
        
        for (int j = i + 1; j < size; j++)
        {
            if (num[j] < num[min])
                min = j;
        }
        
        temp = num[i];
        num[i] = num[min];
        num[min] = temp;
    }
}

int check_i(const int i)
{
    int i_second = i;
    
    if (i == 0)
    {
        printf("Input error");
        return NOT_ARRAY;
    }

    if (i == 11)
    {
        i_second = i - 1;
    }

    return i_second;
}

void printf_array(const int i_second, const int *array)
{
    for (int j = 0; j < i_second; j++)
    {
        printf("%d ", array[j]);
    }
}

int main(void)
{
    int array[MAX_SIZE];
    int i = 0, i_second;

    while (i <= MAX_SIZE - 1 && scanf("%d", &array[i]) == INPUT_OK)
    {
        i ++;
    }
    
    i_second = check_i(i);
    
    if (i_second < 0)
    {
        return NOT_ARRAY;
    }
    
    selection_sort(array, i_second);
    
    printf_array(i_second, array);

    if (i == MAX_SIZE)
    {
        return SPECIAL;
    }
    
    return OK;
}

