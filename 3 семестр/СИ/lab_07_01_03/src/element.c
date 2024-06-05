#include "element.h"

void element_swap(char *one_el, char *two_el, size_t size)
{
    char symbol;
    
    while (size-- > 0)
    {
        symbol = *one_el;
        *(one_el++) = *two_el;
        *(two_el++) = symbol;
    }
}

int comparison_integers(const void *el_1, const void *el_2)
{
    return *((int*) el_1) - *((int*) el_2);
}
