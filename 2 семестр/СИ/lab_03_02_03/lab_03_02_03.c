#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define POSITIVE 1
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define NEG -4
#define NEG_NUMBER -5
#define NOT_DIGIT -6
#define EXCEPTION -7
#define ALL_COLUMN -8
#define MISTAKE_INPUT -4
#define COUNT_COLUMN 1

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

int check_number(void)
{
    int number;

    if (scanf("%d", &number) != INPUT_SIZE)
    {
        return NEG_NUMBER;
    }

    if (number > 9 || number < 0)
    {
        return NOT_DIGIT;
    }

    return number;
}

int check_number_in_array(int element, \
const int number)
{
    element = abs(element);

    if (element == number)
    {
        return OK;
    }

    while (element != 0)
    {
        if (element % 10 == number)
        {
            return OK;
        }

        element /= 10;
    }

    return NEG;
}

void create_new_column(int (*matrix)[MAX_SIZE], \
const int size_row, const int number, const int i, const int j)
{
    if (check_number_in_array(matrix[i][j], number) >= 0)
    {
        for (int i_new = 0; i_new < size_row; i_new++)
        {
            matrix[i_new][j] = number;
        }
    }
}

void create_new_matrix(const int size_column, \
const int size_row, const int number, int (*matrix)[MAX_SIZE])
{
    int j = 0;
	
    while (j != size_column)
    {
        for (int i = 0; i < size_row; i++)
        {
            create_new_column(matrix, size_row, number, i, j);
        }

        j++;
    }
}

int delete_columns (const int size_row, const int size_column, \
int (*matrix)[MAX_SIZE], const int number)
{
    int count;
    
    for (int i = 0; i < size_row * size_column; ++i)
    {
        if (i % size_column == 0)
        {
            count = 0;
        }
        
        if (matrix[i / size_column][i % size_column] != number)
        {
            matrix[i / size_column][count] = \
                matrix[i / size_column][i % size_column];
            count++;
        }
        else
        {
            matrix[i / size_column][i % size_column] = 0;
        }
    }
    
    return count;
}

void print_matrix(const int size_row, const int count, \
int (*matrix)[MAX_SIZE])
{
    for (int i = 0; i < size_row; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}

int main(void)
{
    int size_row, size_column, number, count;
    int matrix[MAX_SIZE][MAX_SIZE] = { 0 };

    if ((size_row = check_size()) < 0)
        return NOT_SIZE_ROW;

    if ((size_column = check_size()) < 0)
        return NOT_SIZE_COLUMN;

    if (read_matrix(matrix, size_row, size_column) < 0)
        return MISTAKE_INPUT;

    if ((number = check_number()) < 0)
        return number;

    create_new_matrix(size_column, size_row, number, matrix);

    if ((count = delete_columns(size_row, size_column, matrix, number)) \
        < COUNT_COLUMN)
        return ALL_COLUMN;
 
    print_matrix(size_row, count, matrix);

    return OK;
}
