#include "list.h"
#include "node.h"

#include <math.h>

node_t *list_add_front(node_t *head, node_t *node)
{
    node->next = head;
    return node;
}

node_t *list_add_end(node_t *head, node_t *node)
{
    if (!head)
        return node;

    node_t *cur = head;
    while (cur->next)
        cur = cur->next;
    
    cur->next = node;

    return head;
}


void list_free(node_t *head)
{
    node_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

void list_print(node_t *head)
{ 
    while (head != NULL)
    {
        printf("%d %d ", head->num, head->power);
        head = head->next;
    }

    puts("1");
}

void list_sqr(node_t **head)
{    
    node_t *tmp = *head;

    while (tmp != NULL)
    {
        tmp->power *= 2;
        tmp = tmp->next;
    }
}

void list_mul(node_t *head_1, node_t *head_2, node_t **head_res)
{    
    node_t *node;

    while (head_1 != NULL && head_2 != NULL)
    {
        if (head_1->num > head_2->num)
        {
            node = node_create(head_1->num, head_1->power);
            *head_res = list_add_end(*head_res, node); 
            head_1 = head_1->next;
        }
        else if (head_2->num > head_1->num)
        {
            node = node_create(head_2->num, head_2->power);
            *head_res = list_add_end(*head_res, node); 
            head_2 = head_2->next;
        }
        else if (head_1->num == head_2->num)
        {
            node = node_create(head_1->num, head_1->power + head_2->power);
            *head_res = list_add_end(*head_res, node); 
            head_1 = head_1->next;
            head_2 = head_2->next;
        }
    }
    
    while (head_1 != NULL)
    {
        node = node_create(head_1->num, head_1->power);
        *head_res = list_add_end(*head_res, node); 
        head_1 = head_1->next;
    }
    while (head_2 != NULL)
    {
        node = node_create(head_2->num, head_2->power);
        *head_res = list_add_end(*head_res, node); 
        head_2 = head_2->next;
    }
}

int list_delete_equal_num(node_t *head_1, node_t *head_2)
{    
    int dividend = 1, divider = 1;

    while (head_1 != NULL && head_2 != NULL)
    {
        if (head_1->num > head_2->num)
        {
            dividend *= pow(head_1->num, head_1->power);
            head_1 = head_1->next;
        }
        else if (head_2->num > head_1->num) 
        {
            divider *= pow(head_2->num, head_2->power);
            head_2 = head_2->next;
        }
        else if (head_1->num == head_2->num)
        {
            if (head_1->power > head_2->power)
                dividend *= pow(head_1->num, head_1->power - head_2->power);
            if (head_2->power > head_1->power)
                divider *= pow(head_1->num, head_2->power - head_1->power);
            
            head_1 = head_1->next;
            head_2 = head_2->next;
        }
    }
    
    while (head_1 != NULL)
    {
        dividend *= pow(head_1->num, head_1->power);
        head_1 = head_1->next;
    }
    while (head_2 != NULL)
    {
        divider *= pow(head_2->num, head_2->power);
        head_2 = head_2->next;
    }
    
    return dividend / divider;
}