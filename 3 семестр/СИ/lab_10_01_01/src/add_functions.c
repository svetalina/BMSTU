#include "add_functions.h"
#include "read_print.h"

node_t *create_node(void *num)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
    
    node->data = num;
    node->next = NULL;

    return node;
}

node_t *list_add_front(node_t *head, void *num)
{
    node_t *node = create_node(num);
    
    if (!node)
        return NULL;
    
    node->next = head;
    return node;
}

int fill_list(node_t **head, year_t *array)
{
    for (int i = array->size - 1; i >= 0; i--)
    {
        if (!(*head = list_add_front(*head, array->array + i)))
        {
            free_list(*head);
            free(array->array);
            return ERROR_MEMORY;
        }
    }

    return EXIT_SUCCESS;
}

void free_list(node_t *head)
{
    node_t *next_elem;

    while (head != NULL)
    {
        next_elem = head->next;

        free(head);
        head = next_elem;
    }
}

int comparator(const void *var1, const void *var2)
{
    return *((int*) var1) - *((int*) var2);
}

void insert_elem(node_t *prev_elem, node_t *next_elem, node_t *element, node_t **head)
{   
    if (!prev_elem)
    {
        element->next = next_elem;
        *head = element;
    }
    else
    {
        prev_elem->next = element;
        element->next = next_elem;
    }
}