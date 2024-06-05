#include "head.h"

int is_sep(const char element)
{
    char sep[LEN_SEP] = " \t\n\r\f\v";
    
    for (int i = 0; i < LEN_SEP - 1; i++)
    {
        if (element == sep[i])
        {
            return YES_SEP;
        }
    }
    
    return NOT_SEP;
}
