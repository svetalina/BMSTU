#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define INPUT_OK 1

#define NEG -1
#define NOT_SQRT -2
#define NOT_SIZE -3
#define OK 0

int check_size(void)
{
    int size_func;
    
    if (scanf("%d", &size_func) != INPUT_OK)
    {
        printf("Input size error");
        return NOT_SIZE;
    }
    
    if (size_func > MAX_SIZE || size_func <= 0)
    {
        printf("Input size error");
        return NOT_SIZE;
    }
    
    return size_func;
}

int check_array(int *array_func, const int size_func, int *array_new_func)
{
    int count = 0;
    
    for (int i = 0; i < size_func; i++)
    {
        if (scanf("%d", &array_func[i]) != INPUT_OK)
        {
            printf("Input array error");
            return NEG;
        }
        
        if ((int)sqrt(array_func[i]) * (int)sqrt(array_func[i]) != array_func[i])
        {
            array_new_func[count] = array_func[i];
            count++;
        }
    }

    return count;
}

int main(void)
{
    int size, count;
    int array[MAX_SIZE] = { 0 }, array_new[MAX_SIZE] = { 0 };

    size = check_size();
    
    if (size < 0)
    {
        return NOT_SIZE;
    }
	
    count = check_array(array, size, array_new);
	
    if (count < 0)
    {
        return count;
    }

    if (count == 0)
    {
        printf("Input sqrt error");
        return NOT_SQRT;
    }

    for (int i = 0; i < count; i += 1)
    {
        printf("%d ", array_new[i]);
    }
	
    return OK;
}

