#include "lab_functions.h"
#include "add_functions.h"
#include "read_print.h"

#define ERRORR_ARGUMENT 4

int main(int argc, const char *argv[])
{
    if (argc != 3)
        return ERRORR_ARGUMENT;
    
    int rc;

    year_t array_a, array_b;
    node_t *head_a = NULL, *head_b = NULL;
    
    if ((rc = read_years(argv[1], &array_a)))   
        return rc;
    if ((rc = fill_list(&head_a, &array_a)))
        return rc;
    
    if ((rc = read_years(argv[2], &array_b)))   
        return rc;
    if ((rc = fill_list(&head_b, &array_b)))
        return rc;
    
    append(&head_a, &head_b);
    remove_duplicates(&head_a, comparator);
    head_a = sort(head_a, comparator);
    head_a = reverse(head_a);
    if (head_a == NULL)
        return ERROR_MEMORY;
   
    print_list(head_a);
    free_list(head_a);
    free(array_a.array);
    free(array_b.array);
    return EXIT_SUCCESS;
}