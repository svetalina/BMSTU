#include <string.h>
#include "head.h"

int is_element_in_array(const char *element, char (*array_word)[MAX_LEN_WORD], \
const int size, const int flag, const int j)
{
    for (int i = 0; i < size; i++)
    {
        if (((flag == F_YES && i != j) || (flag == F_NO)) && \
            strcmp(element, array_word[i]) == 0)
        {
            return IS_NOT_UNIQUE;
        }
    }
    
    return IS_UNIQUE;
}
