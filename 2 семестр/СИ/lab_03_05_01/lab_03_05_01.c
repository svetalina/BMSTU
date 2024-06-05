#include <stdio.h>

#define OK 0
#define NOT_SIZE -1
#define NOT_SIZE_ROW -2
#define NOT_SIZE_COLUMN -3
#define NEG -4
#define NOT_ELEMENT -5
#define MISTAKE_INPUT -6

#define MAX_SIZE 10
#define INPUT_SIZE 1
#define SHIFT 3
#define BASE 10

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

int sum_digit(int num)
{
    int sum = 0;

    while (num != 0)
    {
        sum += num % BASE;
        num = num / BASE;
    }

    return sum;
}

void shift_array(int *array_func, const int size)
{
    if (size == 2)
    {
        int buf = array_func[0];
        array_func[0] = array_func[1];
        array_func[1] = buf;
        return;
    }

    if (size == 1 || size == 3)
    {
        return;
    }

    int buf_a0 = array_func[0], buf_a1 = array_func[1], buf_a2 = array_func[2];

    for (int i = 0; i < size - SHIFT; i++)
    {
        array_func[i] = array_func[i + SHIFT];
    }

    array_func[size - SHIFT] = buf_a0;
    array_func[size - SHIFT + 1] = buf_a1;
    array_func[size - SHIFT + 2] = buf_a2;
}

int check_required_numbers (const int size_row, const int size_column, \
int (*matrix)[MAX_SIZE], int *array_sum, int *position_sum)
{
    int sum_digit_number, count = 0;
    
    for (int i = 0; i < size_row * size_column; ++i)
    {
        sum_digit_number = sum_digit(matrix[i / size_column][i % size_column]);
            
        if (sum_digit_number > 10 || sum_digit_number < -10)
        {
            array_sum[count] = matrix[i / size_column][i % size_column];
            position_sum[count] = i / size_column * size_column + i % \
                size_column;

            count++;
        }
    }
    
    return count;
}

void shift_required_numbers(const int count, const int size_row, \
const int size_column, const int *array_sum, const int *position_sum, \
int (*matrix)[MAX_SIZE])
{
    int row, column;
    
    for (int i = 0; i < SHIFT % count; i++)
    {
        row = position_sum[count - SHIFT % count + i] / size_column;
        column = position_sum[count - SHIFT % count + i] % size_column;

        matrix[row][column] = array_sum[count - SHIFT % count + i];  
    }
}

void shift_unrequired_numbers(const int count, const int size_row, \
const int size_column, const int *array_sum, const int *position_sum, \
int (*matrix)[MAX_SIZE])
{
    int row, column;
    
    for (int i = 0; i < count - SHIFT % count; i++)
    {
        row = position_sum[i] / size_column;
        column = position_sum[i] % size_column;

        matrix[row][column] = array_sum[i];   
    }
}

void print_matrix(int (*matrix)[MAX_SIZE], \
const int size_row, const int size_column)
{
    for (int i = 0; i < size_row; ++i)
    {
        for (int j = 0; j < size_column; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
		
        printf("\n");
    }
}

int main(void)
{
    int size_row, size_column, count;
    int matrix[MAX_SIZE][MAX_SIZE], array_sum[MAX_SIZE], position_sum[MAX_SIZE];

    if ((size_row = check_size()) < 0)
        return NOT_SIZE_ROW;

    if ((size_column = check_size()) < 0)
        return NOT_SIZE_COLUMN;

    if (read_matrix(matrix, size_row, size_column) < 0)
        return MISTAKE_INPUT;
    
    count = check_required_numbers(size_row, size_column, matrix, \
    array_sum, position_sum);

    if (count == 0)
        return NOT_ELEMENT;

    shift_array(array_sum, count);
    
    shift_required_numbers(count, size_row, size_column, array_sum, \
    position_sum, matrix);
    
    shift_unrequired_numbers(count, size_row, size_column, array_sum, \
    position_sum, matrix);
    
    print_matrix(matrix, size_row, size_column);

    return OK;
}
