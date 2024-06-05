#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MISTAKE_INPUT_MAIN -1
#define MISTAKE_OPENING_FILE -2
#define NOT_DIGIT 1

#define NUMBER_MAIN 2
#define NUMBER_NAME_FILE 1
#define INPUT_SIZE 1
#define MAX_START -1000
#define MIN_START 1000

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int count_need_numbers(FILE *f, int max_number, int min_number)
{
    int k = 0;
    float num, sum = 0;
    
    rewind(f);

    while (fscanf (f, "%f", &num) == INPUT_SIZE)
    {
        if (k > MIN(max_number, min_number) && k < MAX(max_number, min_number))
            sum += num;

        k++;
    }
    
    return sum;
}

int get_position_max_min(FILE *f, int *max_number, int *min_number)
{
    int k = 0;
    float num, maximum = MAX_START, minimum = MIN_START;

    while (fscanf (f, "%f", &num) == INPUT_SIZE)
    {
        if (num > maximum)
        {
            maximum = num;
            *max_number = k;
        }
        
        if (num < minimum)
        {
            minimum = num;
            *min_number = k;
        }
        
        k++;
    }
    
    if (k == 0)
        return NOT_DIGIT;

    return OK;
}

int main(int argc, char **argv)
{
    FILE *f; 
    int max_number, min_number;
    
    if (argc != NUMBER_MAIN)
        return MISTAKE_INPUT_MAIN;

    if ((f = fopen(argv[NUMBER_NAME_FILE], "r")) == NULL) 
        return MISTAKE_OPENING_FILE;
    
    if (NOT_DIGIT == get_position_max_min(f, &max_number, &min_number))
        return NOT_DIGIT;
        
    float sum = count_need_numbers(f, max_number, min_number);
    
    printf("%f", sum / (abs(max_number - min_number) - 1));
    
    fclose(f);

    return OK;
}
