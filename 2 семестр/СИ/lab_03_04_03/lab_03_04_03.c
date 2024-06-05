#include <stdio.h>

#define OK 0
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define NOT_SIZE_EQUAL -4
#define MISTAKE_INPUT -5

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

void change_matrix_part_2 (const int i, const int j, const int size, \
int (*matrix)[MAX_SIZE])
{
    int buf;
    
    if ((i >= j) && (i <= size - 1 - j))
    {
        buf = matrix[i][j];
        matrix[i][j] = matrix[i][size - j - 1];
        matrix[i][size - j - 1] = buf;
    }
}

void change_matrix(const int size, int (*matrix)[MAX_SIZE])
{
    for (int j = 0; j < size / 2; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            change_matrix_part_2(i, j, size, matrix);
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
    int matrix[MAX_SIZE][MAX_SIZE] = { 0 };

    if ((size_row = check_size()) < 0)
        return NOT_SIZE_ROW;

    if ((size_column = check_size()) < 0)
        return NOT_SIZE_COLUMN;
    
    if (size_row != size_column)
        return NOT_SIZE_EQUAL;
    
    if (read_matrix(matrix, size_row, size_column) < 0)
        return MISTAKE_INPUT;
    
    change_matrix(size_row, matrix);
    print_matrix(size_row, matrix);

    return OK;
}
