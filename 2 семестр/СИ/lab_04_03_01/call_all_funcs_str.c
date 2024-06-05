#include <string.h>
#include "head.h"

int call_all_funcs_str(char *str)
{
    char *array[MAX_LEN_WORD];
    char new_str[MAX_LEN] = { '\0' };
    
    int size = string_in_words(str, array);
    
    if (size < 2)
        return FEW_WORDS;
    
    for (int i = size - 2; i >= 0; i--)
    {
        if (strcmp(array[i], array[size - 1]) != 0)
        {
            creat_new_str(new_str, array[i]);
        }
    }
    
    if (strlen(new_str) == 0)
        return EMPTY_NEW_STRING;
    
    print_result(new_str);
    return GOOD_NEW_STRING;
}
