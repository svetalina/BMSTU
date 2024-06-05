#include <stdio.h>
#include <string.h>
#include "head.h"

int find_position_not_tab(const char *str)
{
    int i = 0;
    
    while (is_sep(str[i]) == 0 && str[i] != '\0')
    {
        i++;
    }
    
    return i;
}

int check_phone_number(const char *str, const int position_start)
{ 
    int end_code_country = check_code_country(str, position_start);
    
    if (end_code_country < 0)
        return NOT_NUMBER;
    
    if (0 == check_code_operator(str, end_code_country + 1))
        return NOT_NUMBER;
    
    if (0 == check_part_with_d(str, end_code_country + CODE_OPERATORA + 2))
        return NOT_NUMBER;

    return YES_NUMBER;
}

int main(void)
{
    char str[SIZE_STR];
    
    if (!fgets(str, SIZE_STR, stdin) || strlen(str) > MAX_LEN)
        return WRONG_LEN;
    
    int position_start = find_position_not_tab(str);
    
    if (str[position_start] == '\0' || \
        0 == check_phone_number(str, position_start))
    {
        printf("NO");
    }
    else
    {
        printf("YES");
    }
    
    return OK;
}

