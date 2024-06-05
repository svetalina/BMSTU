#include <stdio.h>
#include <math.h>
#define SIZE 10000
#define NEG 1
#define OK 0

float count(float x, int k, float express)
{
    express = express * (x + k);
    return express;
}

int main()
{
    double express = 1.0, g = 1;
    double mas[SIZE] = { 1 };
    int i = 0;
    while (mas[i] >= 0)
    {
        i += 1;
        if (scanf("%lf", &mas[i]) != 1)
        {
            printf("Input error\n");
            return NEG;
        }
    }

    for (int j = 1; j < i; j++)
    {
        express = count(mas[j], j, express);
    }

    g = exp(1 / express);
    printf("%lf", g);

    return OK;
}
