#include "array.h"

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

ARR_DLL int ARR_DECL comparison_integers(const void *el_1, const void *el_2)
{
    return *((int*) el_1) - *((int*) el_2);
}


ARR_DLL int ARR_DECL array_read(int **pb_array, int **pe_array, FILE *const f)
{
    int *begin = *pb_array, *end = *pe_array;
    
    while (begin < end)
        fscanf(f, "%d", begin++); 
    
    if (!feof(f))
        return ERROR_SYMBOL;
    
    return EXIT_SUCCESS;
}

int array_find_last_neg(const int *const begin, const int *const end)
{
    const int *pe = end - 1;
    
    while (pe >= begin)
    {
        if (*pe < 0)
            return (pe - begin);
        pe--;
    }
    
    return (end - begin);
}

void array_fill_new(const int *begin, const int *end, int **begin_fa, int **end_fa)
{
    const int *pb = begin;
    int *pb_fa = *begin_fa;
    
    while (pb < end)
    {
        *(pb_fa++) = *pb;
        pb++;
    }

    *end_fa = pb_fa;
}

ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{   
    if (pb_src == NULL || pe_src == NULL || *pb_dst == NULL || pb_src >= pe_src)
        return ERROR_FILTRATION_DATA;
    
    int ind_last_neg = array_find_last_neg(pb_src, pe_src);
    
    if (ind_last_neg == 0)
        return ERROR_EMPTY_FILTRATION;

    array_fill_new(pb_src, pb_src + ind_last_neg, pb_dst, pe_dst);

    return EXIT_SUCCESS;
}

ARR_DLL void ARR_DECL mysort(void *first, size_t number, size_t size, int (*comparison_integers)(const void *, const void *))
{
    char *begin = first;
    char *end = begin + (number - 1) * size;
    
    for (; begin < end; end -= size)
    {
        for (char *pb = begin, *a, *b; pb < end; pb += size)
        {
            a = pb;
            pb += size;
            b = pb;
            if (comparison_integers(a, b) > 0)
                element_swap(a, b, size);
            pb -= size;
        }
    }
}