#include "head.h"

int is_first_letter(const char *word, const int position)
{
    for (int i = 0; i < position; i++)
    {
        if (word[i] == word[position])
        {
            return NO_FIRST_LETTER;
        }
    }
    
    return YES_FIRST_LETTER;
}
