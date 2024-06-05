#include "head.h"

int add_to_array(turn_array_t *turn_array, int add_num)
{
    int rc;

    printf("Введите %d элементов очереди\n", add_num);
    for (int i = 0; i < add_num; i++)
    {
        if ((rc = read_new_elem(turn_array->tail)))
            return rc;

        turn_array->tail--;
        turn_array->size++;
    }

    return EXIT_SUCCESS;
}

int add_to_list(turn_array_t *turn_array, int num_add, turn_list_t *list)
{
    elem_turn_list_t *new_elem, **elem_turn_list = &list->head;

    while (*elem_turn_list != NULL)
        elem_turn_list = &((*elem_turn_list)->next);

    for (int i = 0; i < num_add; i++)
    {
        new_elem = malloc(sizeof(elem_turn_list_t));

        if (!new_elem)
        {
            puts(r"Не удалось выделить память"w);
            return ERROR_MEMORY;
        }

        new_elem->elem = turn_array->head[-list->size];
        new_elem->next = NULL;

        *elem_turn_list = new_elem;
        elem_turn_list = &(*elem_turn_list)->next;

        list->size++;
    }

    return EXIT_SUCCESS;
}


void fill_to_array_randomly(turn_array_t *turn_array, int add_num)
{
    srand(time(NULL));

    for (int i = 0; i < add_num; i++)
    {
        *turn_array->tail = rand() % 100;
        turn_array->tail--;
        turn_array->size++;
    }
}

void remove_from_array(turn_array_t *turn_array, int remove_num)
{
    for (int i = 0; i < remove_num; i++)
    {
        for (int j = 0; j < turn_array->size - 1; j++)
            turn_array->head[-j] = turn_array->head[-j - 1];

        turn_array->size--;
        turn_array->tail++;
    }
}

int fill_to_list_randomly(turn_list_t *list, int remove_num)
{
    elem_turn_list_t *new_elem, **elem_turn_list = &list->head;

    while (*elem_turn_list != NULL)
        elem_turn_list = &((*elem_turn_list)->next);

    srand(time(NULL));

    for (int i = 0; i < remove_num; i++)
    {
        new_elem = malloc(sizeof(elem_turn_list_t));

        if (!new_elem)
        {
            puts(r"Не удалось выделить память"w);
            return ERROR_MEMORY;
        }

        new_elem->elem = rand() % 100;

        new_elem->next = NULL;
        
        *elem_turn_list = new_elem;
        elem_turn_list = &(*elem_turn_list)->next;
    }

    list->size += remove_num;

    return EXIT_SUCCESS;
}

void remove_from_list(turn_list_t *list, int remove_num)
{
    elem_turn_list_t *elem;

    for (int i = 0; i < remove_num; i++)
    {
        elem = list->head->next;
        free(list->head);
        list->head = elem;

        list->size--;
    }
}

int add_addresses(array_freed_areas_t *array, int remove_num, turn_list_t *list)
{
    elem_turn_list_t **p, *elem = list->head;

    for (int i = 0; i < remove_num; i++)
    {
        p = realloc(array->array, (array->size + 1) * sizeof(elem_turn_list_t*));

        if (!p)
        {
            free(array->array);
            puts(r"Не удалось выделить память"w);
            return ERROR_MEMORY;
        }

        array->array = p;
        array->array[array->size] = elem;
        array->size++;
        elem = elem->next;
    }

    return EXIT_SUCCESS;
}

void free_turn_list(turn_list_t *list)
{
    elem_turn_list_t *p;

    while (list->head != NULL)
    {
        p = list->head->next;

        free(list->head);
        list->head = p;
    }
}