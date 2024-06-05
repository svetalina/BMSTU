#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "head.h"

int main(void)
{
    char str[MAX_LEN];
    
    if (fgets(str, MAX_LEN, stdin) == NULL || strlen(str) >= MAX_LEN - 1 \
        || strlen(str) < 2)
    {
        return MISTAKE_STR;
    }

    if (call_all_funcs_str(str) < 0)
    {
        return MISTAKE_NEW_STR;
    }
    
    return OK;
}
