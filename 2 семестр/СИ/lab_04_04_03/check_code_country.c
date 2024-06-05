#include "head.h"

int check_code_country(const char *str, const int position_start)
{
    if (str[position_start] == '(')
        return position_start;
    
    if (str[position_start] != '+')
        return NOT_CODE_COUNTRY;
    
    int i = position_start + 1;
    
    while (str[i] != '(' && str[i] != '\0')
    {
        if (0 == check_digit(str[i]))
            return NOT_CODE_COUNTRY;
        
        i++;
    }
    
    if (i == position_start + 1 || str[i] == '\0')
        return NOT_CODE_COUNTRY;
    
    return i;
}
