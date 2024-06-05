#include "element.h"
#include "array.h"

int array_read(int **pb_array, int **pe_array, FILE *const f)
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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{   
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
        return ERROR_FILTRATION_DATA;
    
    int ind_last_neg = array_find_last_neg(pb_src, pe_src);
    
    if (ind_last_neg == 0)
        return ERROR_EMPTY_FILTRATION;
	
    if ((*pb_dst = malloc((ind_last_neg + 1) * sizeof(int))) == NULL)
        return ERROR_MEMORY;

    array_fill_new(pb_src, pb_src + ind_last_neg, pb_dst, pe_dst);

    return EXIT_SUCCESS;
}


void mysort(void *first, size_t number, size_t size, int (*comparison_integers)(const void *, const void *))
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
