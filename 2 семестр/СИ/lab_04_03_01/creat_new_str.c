#include <string.h>
#include "head.h"

void creat_new_str(char *new_str, const char *word)
{
    int i = 0, k = strlen(new_str);
    
    while (word[i] != '\0')
    {
        if (is_first_letter(word, i))
        {
            new_str[k++] = word[i];
        }
        
        i++;
    }
    
    new_str[k] = ' ';
}
