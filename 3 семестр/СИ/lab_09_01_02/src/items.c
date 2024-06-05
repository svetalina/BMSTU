#include "item.h"
#include "items.h"

int items_change_memory(item_t **array, int size)
{
    item_t *ptr = realloc(*array, size * sizeof(item_t));
    if (!ptr)
        return ERROR_MEMORY;

    *array = ptr;
    ptr = NULL;

    return EXIT_SUCCESS;
}

void items_free_memory(item_t **array, int size)
{
    for (int i = 0; i < size; i++)
        free((*array + i)->name);
	
    free(*array);
}

int items_read(FILE *f, item_t **array)
{
    int rc;
    
    *array = NULL;
    int num_buf = 0, num_el = 0;
    
    while (!feof(f)) 
    {
        if (num_buf == num_el)
        {
            num_buf = num_buf == 0 ? 1 : num_buf * 2;
            if ((rc = items_change_memory(array, num_buf)))
            {
                items_free_memory(array, num_el);
                return rc;
            }
        }
		
        if ((rc = item_read(f, *array + num_el++)))
        {
            items_free_memory(array, num_el);
            return rc;
        }
    }
	
    return num_el;
}

void items_print(item_t **array, int size)
{
    for (size_t i = 0; i < size; i++)
        item_print(*array + i);
}

void items_sort(item_t **array, int size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            item_compare(*array + j - 1, *array + j);
}
