#include "item.h"
#include "items.h"

int items_read(FILE *f, item_t *array)
{
    int i = 0, rc;
    
    while (!(feof(f)) && !(rc = item_read(f, &(array[i]))))
        if (++i >= ARRAY_SIZE)
            return ERROR_STRUCT_SIZE;
        
    if (rc != 0)
        return rc;
 
    return i;
}

void items_print(item_t *array, int size)
{
    for (size_t i = 0; i < size; i++)
        item_print(&(array[i]));
}

void items_sort(item_t *array, int size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = (size - 1); j > i; j--)
            item_compare(&(array[j - 1]), &(array[j]));
}
