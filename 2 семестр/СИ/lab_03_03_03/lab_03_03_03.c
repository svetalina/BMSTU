#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define MISTAKE_INPUT -4

#define MAX_SIZE 10
#define INPUT_SIZE 1
#define MIN_DEFINE 1000
#define BASE 100

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

int find_min(const int *array_func, const int len)
{
    int min = MIN_DEFINE;

    for (int i = 0; i < len; i++)
    {
        if (array_func[i] < min)
        {
            min = array_func[i];
        }
    }

    return min;
}

void selection_sort(int *num, const int size)
{
    int max, temp;

    for (int i = 0; i < size - 1; i++)
    {
        max = i;

        for (int j = i + 1; j < size; j++)
        {
            if (num[j] / BASE > num[max] / BASE)
            {
                max = j;
            }
        }

        temp = num[i];
        num[i] = num[max];
        num[max] = temp;
    }
}

void check_minimun(const int size_row, const int size_column, \
int (*matrix)[MAX_SIZE], int *array_min)
{
    int i_plus, minimum;
    
    for (int i = 0; i < size_row; i++)
    {
        minimum = find_min(matrix[i], size_column);

        i_plus = i;

        if (minimum < 0)
        {
            i_plus = -i;
        }

        array_min[i] = minimum * BASE + i_plus;
    }
}

void print_matrix(const int size_row, const int size_column, \
int (*matrix)[MAX_SIZE], const int *array_min)
{
    int row;
    
    for (int i = 0; i < size_row; ++i)
    {
        row = abs(array_min[i]) % BASE;

        for (int j = 0; j < size_column; ++j)
        {
            printf("%d ", matrix[row][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int size_row, size_column;
    int matrix[MAX_SIZE][MAX_SIZE], array_min[MAX_SIZE];

    if ((size_row = check_size()) < 0)
        return NOT_SIZE_ROW;

    if ((size_column = check_size()) < 0)
        return NOT_SIZE_COLUMN;

    if (read_matrix(matrix, size_row, size_column) < 0)
        return MISTAKE_INPUT;

    check_minimun(size_row, size_column, matrix, array_min);
    selection_sort(array_min, size_row);
    print_matrix(size_row, size_column, matrix, array_min);

    return OK;
}
