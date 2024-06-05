#include "head.h"

int check_digit(const int digit)
{
    if (digit <= '9' && digit >= '0')
    {
        return YES_DIGIT;
    }
    
    return NOT_DIGIT;
}

