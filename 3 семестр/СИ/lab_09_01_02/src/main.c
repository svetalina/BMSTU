#include <string.h>
#include "item.h"
#include "items.h"

int main(int argc, char **argv)
{   
    if (argc != 2 && argc != 3)
        return ERROR_MAIN;
    
    item_t *array;
    int size;
    FILE *f;
    
    if ((f = fopen(argv[1], "r")) == NULL)
        return ERROR_OPEN;    
    if ((size = items_read(f, &array)) < 1)
    {
        fclose(f);
        return size;
    }
    
    if (2 == argc)
    {
        items_sort(&array, size);
        items_print(&array, size);
    }
    
    if (3 == argc && 0 == strcmp(argv[2], "ALL"))
        items_print(&array, size);
    
    if (3 == argc && 0 != strcmp(argv[2], "ALL"))
        for (int i = 0; i < size; i++)
            if (strstr(array[i].name, argv[2]) == array[i].name)
                item_print(&array[i]);
    
    items_free_memory(&array, size);
    fclose(f);
    return EXIT_SUCCESS;
}
