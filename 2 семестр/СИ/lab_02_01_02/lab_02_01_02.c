#include <stdio.h>

#define MAX_SIZE 10
#define INPUT_OK 1

#define NEG 1
#define NOT_MINUS 2
#define NOT_SIZE -1
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

int processing_array(int *array_func, const int size_func)
{
    float sum = 0;
    int count_negative = 0;
    
    for (int i = 0; i < size_func; i++)
    {
        if (scanf("%d", &array_func[i]) != INPUT_OK)
        {
            printf("Input array error");
            return NEG;
        }
        
        if (array_func[i] < 0)
        {
            sum += array_func[i];
            count_negative ++;
        }
    }

    if (count_negative == 0)
    {
        printf("Input minus error");
        return NOT_MINUS;
    }
	
    printf("%f", sum / count_negative);
    return OK;
}

int main(void)
{
    int size, ending;
    int array[MAX_SIZE] = { 0 };

    size = check_size();
    
    if (size < 0)
    {
        return NOT_SIZE;
    }
	
    ending = processing_array(array, size);
	
    return ending;
}
