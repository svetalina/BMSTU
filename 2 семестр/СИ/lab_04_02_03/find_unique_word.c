#include <stdio.h>
#include "head.h"

int find_unique_word(char (*array_word_first)[MAX_LEN_WORD], char \
    (*array_word_second)[MAX_LEN_WORD], const int size_first, const int size_second)
{
    int flag = 0;
    
    for (int i = 0; i < size_first; i++)
    {
        if (is_element_in_array(array_word_first[i], array_word_second, \
        size_second, F_NO, i) > 0 && is_element_in_array(array_word_first[i], \
        array_word_first, size_first, F_YES, i) > 0)
        {
            flag = print_result(flag);
            printf("%s ", array_word_first[i]);
        }
    }
    
    for (int i = 0; i < size_second; i++)
    {
        if (is_element_in_array(array_word_second[i], array_word_first, \
        size_first, F_NO, i) > 0 && is_element_in_array(array_word_second[i], \
        array_word_second, size_second, F_YES, i) > 0)
        {
            flag = print_result(flag);
            printf("%s ", array_word_second[i]);
        }
    }
    
    return flag;
}
