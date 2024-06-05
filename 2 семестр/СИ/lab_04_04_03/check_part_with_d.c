#include <stdio.h>
#include <string.h>
#include "head.h"

int check_part_with_d(const char *str, const int position_start)
{
    int position_end = position_start + COUNT_D_ONE + \
        COUNT_D_TWO * NUMBER_OF_PARTS + NUMBER_OF_HYPHENS;
    
    for (int i = position_start; i < position_end; i++)
    {
        if (str[i] == '\0')
            return NOT_D;
        
        if (str[i] != '-' && (i == position_start || i == position_start + \
        COUNT_D_ONE + 1 || i == position_end))
            return NOT_D;

        if (0 == check_digit(str[i]) && str[i] != '-')
            return NOT_D;
    }
    
    if (0 != is_sep(str[position_end]) && str[position_end] != '\0')
        return NOT_D;
    
    return YES_D;
}
