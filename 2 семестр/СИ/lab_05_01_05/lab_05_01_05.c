#include <stdio.h>

#define NOT_DIGIT 2
#define OK 0

#define INPUT_SIZE 1

int process(FILE *f)
{
    int previous_el, num;
    
    if (fscanf (f, "%d", &previous_el) != INPUT_SIZE)
        return NOT_DIGIT;
    
    int max_len = 1, k = 1;
    
    while (fscanf (f, "%d", &num) == INPUT_SIZE)
    {
        if (num == previous_el)
            k++;
        else
            k = 1;
        
        max_len = (k > max_len) ? k : max_len;
        
        previous_el = num;
    }
    
    printf("%d", max_len);
    
    return OK;
}


int main(void)
{
    FILE *f = stdin;
    
    if (process(f))
    {
        return NOT_DIGIT;
    }

    return OK;
}
