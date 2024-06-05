#include <stdio.h>
#include <math.h>
#define NEG 1
#define NOT_ABS 2
#define NOT_SEGMENT 3

double s_func(double x, double eps)
{
    int k = 2, sign = -1;
    double x_number = 1, s_x = 0, x_func = x;

    while (fabs(x_number) > eps)
    {
        s_x = s_x + x_number;
        x_number = sign * k * (k + 1) * x_func / 2;

        sign *= -1;
        k = k + 1;
        x_func *= x;
    }

    return s_x;
}

int main()
{
    double x, eps;

    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("Input error\n");
        return NEG;
    }
    else if (fabs(x) >= 1)
    {
        printf("Input abs error\n");
        return NOT_ABS;
    }
    else if (eps <= 0 || eps > 1)
    {
        printf("Input segment error\n");
        return NOT_SEGMENT;
    }
    else
    {
        double f, s, del, sig;

        f = 1 / ((1 + x) * (1 + x) * (1 + x));
        s = s_func(x, eps);
        del = fabs(f - s);
        sig = fabs((f - s) / f);
        printf("%lf %lf %lf %lf", s, f, del, sig);
    }

    return 0;
}