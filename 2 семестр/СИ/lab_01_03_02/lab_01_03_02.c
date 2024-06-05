#include <stdio.h>
#define OK 0

int main(void)
{
    float resistance_1, resistance_2, resistance_3, resistance_all;
    scanf("%f%f%f", &resistance_1, &resistance_2, &resistance_3);

    if (resistance_1 != 0 || resistance_2 != 0 || resistance_3 != 0)
    {
        resistance_all = (resistance_1 * resistance_2 * resistance_3) / \
            (resistance_1 * resistance_3 + resistance_2 * resistance_3 + resistance_1 * resistance_2);
        
        printf("%.4g", resistance_all);
    }
    else
    {
        printf("Resistance is impossible to find");
    }

    return OK;
}