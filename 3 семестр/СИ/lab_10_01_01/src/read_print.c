#include "read_print.h"

int read_years(const char *file_name, year_t *array)
{   
    FILE *f;
    if (!(f = fopen(file_name, "r")))
        return ERROR_OPEN_FILE;

    int *p;

    array->array = NULL;
    array->size = 0;

    while (!feof(f))
    {
        if (!(p = realloc(array->array, (array->size + 1) * sizeof(int))))
        {
            free(array->array);
            fclose(f);
            return ERROR_MEMORY;
        }
        array->array = p;

        if (fscanf(f, "%d", array->array + array->size) != 1)
        {
            free(array->array);
            fclose(f);
            return ERROR_READING;
        }
        
        array->size++;
    }
    
    fclose(f);
    return EXIT_SUCCESS;
}

void print_list(node_t *head)
{
    node_t *p = head;
    while (p != NULL)
    {
        printf("%d\n", *(int*) p->data);
        p = p->next;
    }
}