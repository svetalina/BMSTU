#include "head.h"

int check_code_operator(const char *str, const int position_start)
{
    if (str[position_start + CODE_OPERATORA] != ')')
    {
        return NOT_CODE_OPERATOR;
    }
    
    for (int i = position_start; i < position_start + CODE_OPERATORA; i++)
    {
        if (0 == check_digit(str[i]))
        {
            return NOT_CODE_OPERATOR;
        }
    }
    
    return YES_CODE_OPERATOR;
}

