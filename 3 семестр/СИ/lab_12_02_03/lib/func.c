#include <stdlib.h>

static int check_prime_num(int num)
{
	for (int i = 2; i < num; i++)
		if (num % i == 0)
			return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static int find_next_prime(int num)
{
	do
		num++;
    while (check_prime_num(num));
	
    return num;
}

void fill_array(int *array, int size)
{
    int prime_num = 2;
    for (int i = 0; i < size; i++)
    {
        array[i] = prime_num;
        prime_num = find_next_prime(prime_num);
    }
}

static int check_even_num(int num)
{
	if (num % 2 != 0)
		return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int fill_array_after_even(int *arr, int size, int *arr_res, int size_res, int num)
{
	int ind = 0;
    for (int i = 0; i < size; i++)
    {
        if (ind < size_res)
            arr_res[ind] = arr[i];
		ind++;
		
        if (!check_even_num(arr[i]))
		{
            if (ind < size_res)
				arr_res[ind] = num;
			ind++;
		}		
    }

    return ind;
}