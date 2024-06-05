#include <stdio.h>

#define OK 0
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define MISTAKE_INPUT -4

#define MAX_SIZE 10
#define INPUT_SIZE 1

int check_size(void)
{
    int size;

    if (scanf("%d", &size) != INPUT_SIZE)
    {
        return NOT_SIZE;
    }

    if (size > MAX_SIZE || size <= 0)
    {
        return NOT_SIZE;
    }

    return size;
}

int read_matrix(int matrix[MAX_SIZE][MAX_SIZE], const int size_row, \
const int size_column)
{
    int size = size_row * size_column;
	
    for (int i = 0; i < size; i++)
    {
        if (scanf("%d", &matrix[i / size_column][i % size_column]) \
            != INPUT_SIZE)
        {
            return MISTAKE_INPUT;
        }
    }

    return OK;
}

int is_monotone(const int *array_func, const int len)
{
    int i = 1, flag = 0;

    while (flag < len - 1 && array_func[i] >= array_func[i - 1])
    {
        flag++;
        i++;
    }

    if (flag != 0)
    {
        return flag;
    }

    while (flag < len - 1 && array_func[i] <= array_func[i - 1])
    {
        flag++;
        i++;
    }

    return flag;
}

void create_array(const int size_column, const int size_row, \
int matrix[MAX_SIZE][MAX_SIZE], int *array_new)
{
    if (size_column == 1)
    {
        return;
    }

    for (int i = 0; i < size_row; i++)
    {
        if (is_monotone(matrix[i], size_column) == size_column - 1)
        {
            array_new[i] = 1;
        }
    }
}

void print_array(const int size_row, const int *array_new)
{
    for (int i = 0; i < size_row; i++)
    {
        printf("%d ", array_new[i]);
    }
}

int main(void)
{
    int matrix[MAX_SIZE][MAX_SIZE], array_new[MAX_SIZE] = { 0 };

    int size_row, size_column;

    if ((size_row = check_size()) < 0)
    {
        return NOT_SIZE_ROW;
    }

    if ((size_column = check_size()) < 0)
    {
        return NOT_SIZE_COLUMN;
    }

    if (read_matrix(matrix, size_row, size_column) < 0)
    {
        return MISTAKE_INPUT;
    }

    create_array(size_column, size_row, matrix, array_new);
    print_array(size_row, array_new);

    return OK;
}
