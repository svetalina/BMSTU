#include <stdio.h>
#include <string.h>
#include "head.h"

int main(void)
{
    char str_first[MAX_LEN], str_second[MAX_LEN];
    char array_word_first[MAX_LEN][MAX_LEN_WORD] = { '\0' };
    char array_word_second[MAX_LEN][MAX_LEN_WORD] = { '\0' };
    
    if (!fgets(str_first, MAX_LEN, stdin) || strlen(str_first) > MAX_LEN - 1)
        return MISTAKE_STR_FIRST;
    
    if (!fgets(str_second, MAX_LEN, stdin) || strlen(str_second) > MAX_LEN - 1)
        return MISTAKE_STR_SECOND;

    if (strlen(str_first) < MIN_LEN && strlen(str_second) < MIN_LEN)
        return MISTAKE_STRLEN;

    int size_first = string_in_words(str_first, array_word_first);
    int size_second = string_in_words(str_second, array_word_second);
    
    if (find_unique_word(array_word_first, array_word_second, \
    size_first, size_second) == 0)
        return MISTAKE_SIZE;

    return OK;
}
