#include <stdio.h>

#define OK 0
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define NOT_SIZE_EQUAL -4

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

void check_array(int (*matrix)[MAX_SIZE], const int size)
{
    int count = 1;

    for (int loop = 1; loop <= size / 2 + size % 2; loop++)
    {
        for (int j = loop - 1; j < size - loop + 1; j++)
        {
            matrix[j][loop - 1] = count++;
        }

        for (int j = loop; j < size - loop + 1; j++)
        {
            matrix[size - loop][j] = count++;
        }

        for (int j = size - loop - 1 ; j >= loop - 1; --j)
        {
            matrix[j][size - loop] = count++;
        }

        for (int j = size - loop - 1; j >= loop; j--)
        {
            matrix[loop - 1][j] = count++;
        }
    }
}

void print_matrix(const int size, int (*matrix)[MAX_SIZE])
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int size_row, size_column;
    int matrix[MAX_SIZE][MAX_SIZE];

    if ((size_row = check_size()) < 0)
        return NOT_SIZE_ROW;

    if ((size_column = check_size()) < 0)
        return NOT_SIZE_COLUMN;
    
    if (size_row != size_column)
        return NOT_SIZE_EQUAL;

    check_array(matrix, size_row);
    
    print_matrix(size_row, matrix);

    return OK;
}
