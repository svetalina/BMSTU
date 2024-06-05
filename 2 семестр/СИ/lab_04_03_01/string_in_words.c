#include <string.h>
#include <stddef.h>
#include "head.h"

int string_in_words(char *str, char **array)
{
    char sep[LEN_SEP] = " ,;:-.!?\n\t\r\f\v";
    char *istr;

    istr = strtok(str, sep);
   
    int i = 0;

    while (istr != NULL)
    {
        if (strlen(istr) > MAX_LEN_WORD - 2)
        {
            return TOO_LONG_WORD;
        }
        
        array[i] = istr;
        i++;
        istr = strtok(NULL, sep);
    }

    return i;
}
