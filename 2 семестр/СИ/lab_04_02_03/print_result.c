#include <stdio.h>
#include "head.h"

int print_result(const int is_ok)
{
    if (is_ok == 0)
    {
        printf("Result: ");
    }
    
    return IS_OK_PRINT;
}

