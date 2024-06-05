#include <stdio.h>
#include <string.h>
#include "head.h"

void print_result(char *new_str)
{
    new_str[strlen(new_str) - 1] = '\0';
    
    printf("Result: %s\n", new_str);
}
