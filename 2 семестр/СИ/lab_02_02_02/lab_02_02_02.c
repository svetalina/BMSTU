#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define INPUT_OK 1
#define DIGIT_EQUAL_OK 1
#define DIGIT_EQUAL_NEG 0

#define NEG -1
#define NOT_SIZE -2
#define NOT_DIGIT -3
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

int digit_equal(int element)
{
    int el_10;
	
    element = abs(element);

    el_10 = element % 10;

    while (element > 9)
    {
        element /= 10;
    }
	
    if (el_10 == element)
    {
        return DIGIT_EQUAL_OK;
    }
	
    return DIGIT_EQUAL_NEG;
}

int element_equal_array(int *array_func, const int size_func, int *array_new)
{
    int count_equal_func = 0;
	
    for (int i = 0; i < size_func; i++)
    {
        if (scanf("%d", &array_func[i]) != INPUT_OK)
        {
            printf("Input array error");
            return NEG;
        }

        if (digit_equal(array_func[i]) == 1)
        {
            array_new[count_equal_func] = array_func[i];
            count_equal_func++;
        }
    }
	
    return count_equal_func;
}

int check_count_equal(int const *array_new_func, const int count_equal_func)
{
    if (count_equal_func < 0)
    {
        return NEG;
    }
	
    if (count_equal_func == 0)
    {
        printf("Input digit error");
        return NOT_DIGIT;
    }

    for (int i = 0; i < count_equal_func; i++)
    {
        printf("%d ", array_new_func[i]);
    }
	
    return OK;
}

int main(void)
{
    int size, count_equal, ending;
    int array[MAX_SIZE] = { 0 }, array_new[MAX_SIZE] = { 0 };

    size = check_size();
    
    if (size < 0)
    {
        return NOT_SIZE;
    }
	
    count_equal = element_equal_array(array, size, array_new);
	
	
    ending = check_count_equal(array_new, count_equal);
	
    return ending;
}

