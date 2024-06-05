#include <stdio.h>
#include <stdint.h>
#define SIZE 32
#define NEG 1
#define NOT_SHIFT 2
#define OK 0

uint32_t func(uint32_t a, int n)
{
    a = (a << n) | (a >> (SIZE - n));
    return a;
}

int main()
{
    uint32_t a;
    int n;
    if (scanf("%u%d", &a, &n) != 2)
    {
        printf("Error: not integers entered\n");
        return NEG;
    }
    else if (n < 0)
    {
        printf("Error: 'n' negative\n");
        return NOT_SHIFT;
    }
    else
    {
        a = func(a, n);
        printf("Result: ");
        for (int i = SIZE - 1; i >= 0; i -= 1)
        {
            printf("%u", (a >> i) % 2);
        }
    }

    return OK;
}
