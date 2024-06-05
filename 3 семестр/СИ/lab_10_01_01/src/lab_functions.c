#include "lab_functions.h"
#include "add_functions.h"
#include "read_print.h"

void append(node_t **head_a, node_t **head_b)
{
    if (!head_a || !head_b || !(*head_b))
        return;
    
    if (!(*head_a))
    {
        *head_a = *head_b;
        *head_b = NULL; 
        return;
    }

    node_t *cur_a = *head_a;
    while (cur_a->next)
        cur_a = cur_a->next;
    cur_a->next = *head_b;  
    
    *head_b = NULL; 
}

void remove_duplicates(node_t **head,
int (*comparator)(const void*, const void*))
{
    node_t *cur = *head;
    node_t *tmp, *prev_elem, *next_elem;
    
    for (; cur != NULL; cur = cur->next)
    {
        prev_elem = cur; 
        for (next_elem = cur->next; next_elem != NULL;)  
        {
            if (!(comparator(next_elem->data, cur->data)))
            {
                tmp = prev_elem->next = next_elem->next;
                free(next_elem);
                next_elem = tmp;
                continue; 
            }
            prev_elem = next_elem;
            next_elem = next_elem->next;
        }
    }
}

void sorted_insert(node_t **head, node_t *element,
int (*comparator)(const void*, const void*))
{
    node_t *elem_list = *head, *prev_elem = NULL;

    while (elem_list)
    {
        if (comparator(element->data, elem_list->data) < 0)
        {
            insert_elem(prev_elem, elem_list, element, head);
            return;
        }

        prev_elem = elem_list;
        elem_list = elem_list->next;
    }

    insert_elem(prev_elem, NULL, element, head);
}

node_t *sort(node_t *head, int (*comparator)(const void*, const void*))
{
    node_t *new_head = NULL, *elem = head, *next_elem;

    while (elem)
    {
        next_elem = elem->next;
        sorted_insert(&new_head, elem, comparator);
        elem = next_elem;
    }

    return new_head;
}

void *pop_front(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    void *required_data = (*head)->data;

    node_t *tmp = *head;
    *head = (*head)->next;
    free(tmp);

    return required_data;
}

node_t *reverse(node_t *head)
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;
    node_t *tmp = head;

    while (tmp != NULL)
    {
        void *data = pop_front(&tmp);
        
        if (!(new_head = list_add_front(new_head, data)))
            return NULL;
    }

    return new_head;
}
