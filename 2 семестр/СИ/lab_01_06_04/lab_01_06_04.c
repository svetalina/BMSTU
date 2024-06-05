#include <stdio.h>
#include <math.h>
#define EPS 0.000001
#define YES 1
#define NO 0
#define NEG -1
#define NOT_SEGMENT -2
#define OK 0

int сollinearity(double xp, double yp, double xq, double yq, double xr, double yr)
{
    int ok_func;

    if (fabs((xp - xq) * (yr - yq) - (xr - xq) * (yp - yq)) < EPS)
    {
        ok_func = 1;
    }
    else
    {
        ok_func = 0;
    }

    return ok_func;
}

int segment(double xp, double yp, double xq, double yq, double xr, double yr)
{
    int is_ok = 0;

    if ((xq < xp && xp < xr) || (xq > xp && xp > xr))
    {
        is_ok = 1;
    }
    else if ((yq < yp && yp < yr) || (yq > yp && yp > yr))
    {
        is_ok = 1;
    }

    return is_ok;
}

int main()
{
    double xq, yq, xr, yr, xp, yp;

    if (scanf("%lf%lf%lf%lf%lf%lf", &xq, &yq, &xr, &yr, &xp, &yp) != 6)
    {
        printf("Input error\n");
        return NEG;
    }

    if (fabs(xq - xr) < EPS && fabs(yq - yr) < EPS)
    {
        printf("Input segment error\n");
        return NOT_SEGMENT;
    }

    if ((fabs(xq - xp) < EPS && fabs(yq - yp) < EPS) || (fabs(xr - xp) < EPS && fabs(yr - yp) <EPS))
    {
        printf("%d", YES);
    }
    else if (сollinearity(xp, yp, xq, yq, xr, yr) == 1 &&  segment(xp, yp, xq, yq, xr, yr) == 1)
    {
        printf("%d", YES);
    }
    else
    {
        printf("%d", NO);
    }
    return OK;
}

