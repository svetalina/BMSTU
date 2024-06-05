#include <stdio.h>
#define NEG 1
#define OK 0

int nod(int a, int b)
{
    while (a != b)
    {
        if (a > b) 
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    return a;
}

int main()
{
    int number_1, number_2, nod_int;
    if (scanf("%d%d", &number_1, &number_2) == 2)
    {
        nod_int = nod(number_1, number_2);
        printf("%d", nod_int);
    }
    else
    {
        printf("Input error\n");
        return NEG;
    }
    return OK;
}

