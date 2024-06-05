#include <string.h>
#include "head.h"

int string_in_words(char *str, char (*array_word)[MAX_LEN_WORD])
{
    int k = 0, row = -1, j = 0, row_for_sep = 0;

    str[strlen(str) - 1] = '\0';
    
    while (str[k] != '\0')
    {
        if (element_is_sep(str[k]) < 0)
        {
            row_for_sep = row + 1;
            j = 0;
        }
        else
        {
            row = row_for_sep;
            array_word[row][j] = str[k];
            j++;
        }
        
        k++;
    }
    
    return row + 1;
}