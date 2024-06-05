#include <stddef.h>

#define YES_STRCSPN 0
#define NO_STRCSPN 1

size_t my_strcspn(const char *str_first, const char *str_second)
{
    int i = 0, len = 0, flag = 1, count_hit;

    while (str_first[i] && flag)
    {
        count_hit = 0;
        
        while (str_second[count_hit] && flag)
        {
            flag = (str_first[i] == str_second[count_hit]) ? YES_STRCSPN : NO_STRCSPN;

            count_hit++;
        }
        
        if (flag)
        {
            len++;
        }
        
        i++;
    }
    return len;
}
