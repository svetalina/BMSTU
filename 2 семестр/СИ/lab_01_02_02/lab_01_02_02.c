#include <stdio.h>
#include <math.h>

int main(void)
{
    float xa, ya, xb, yb, xc, yc;
    scanf("%f%f", &xa, &ya);
    scanf("%f%f", &xb, &yb);
    scanf("%f%f", &xc, &yc);

    float ab, bc, ac, perimeter, perimeter_half;
    ab = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
    bc = sqrt((xb - xc) * (xb - xc) + (yb - yc) * (yb - yc));
    ac = sqrt((xa - xc) * (xa - xc) + (ya - yc) * (ya - yc));

    perimeter = ab + bc + ac;
    perimeter_half = perimeter / 2;

    const float eps = 0.00001;
    float square;
    square = sqrt(perimeter_half * (perimeter_half - ab) * (perimeter_half - bc) * (perimeter_half - ac));
    if (square > eps)
    {
        printf("%.5g", perimeter);
    }
    else
    {
        perimeter = 0;
        printf("%.5g", perimeter);
    }

    return 0;
}