#include "head.h"

int element_is_sep(const char element)
{
    char sep[LEN_SEP] = " ,;:-.!?";
    
    for (int i = 0; i < LEN_SEP; i++)
    {
        if (element == sep[i])
        {
            return IS_SEP; 
        }
    }
    
    return IS_NOT_SEP;
}
