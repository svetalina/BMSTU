#include "head.h" 

int stack_list(void)
{
    int rc;
    
    int action_type;
    el_stack_list_t *el_stack_list = NULL;
    array_free_areas_t array = {NULL, 0};

    while(1)
    {

        if ((rc = read_action_type(&action_type)))
        {
            free_stack_list(&el_stack_list);
            free(array.array);
            return rc;
        }
        
        if (action_type == 1)
        {   
            int num_add;
            if ((rc = read_num_to_add_stack_list(&num_add, el_stack_list)))
            {
                free_stack_list(&el_stack_list);
                free(array.array);
                return rc;
            }
            
            add_stack_list(&el_stack_list, num_add);
        }
        
        if (action_type == 2)
        {
            int num_add;
            if ((rc = read_num_to_add_stack_list(&num_add, el_stack_list)))
            {
                free_stack_list(&el_stack_list);
                free(array.array);
                return rc;
            }
                
            add_stack_list_random(&el_stack_list, num_add);
        }
        
        if (action_type == 3)
        {
            int num_remove;

            if ((rc = read_num_to_remove_stack_list(&num_remove, el_stack_list)))
            {
                free_stack_list(&el_stack_list);
                free(array.array);
                return rc;
            }

            if (el_stack_list != NULL)
            {
                if ((rc = add_addresses(&array, num_remove, el_stack_list)))
                {
                    free_stack_list(&el_stack_list);
                    return rc;
                }

                remove_stack_list(&el_stack_list, num_remove);
            }
        }
        
        if (action_type == 4)
        {
            print_stack_list(&el_stack_list);
            print_array(&array);
        }
        
        if (action_type == 5)
        {
            check_brackets_list(&el_stack_list);
        }
        
        if (action_type == 0)
        {
            free_stack_list(&el_stack_list);
            free(array.array);
            break;
        }
    }

    return EXIT_SUCCESS;
}

void free_stack_list(el_stack_list_t **el_stack_list)
{
    el_stack_list_t *p;

    while (*el_stack_list != NULL)
    {
        p = (*el_stack_list)->next;
        free(*el_stack_list);
        *el_stack_list = p;
    }
}

int add_stack_list(el_stack_list_t **el_stack_list, int num_add)
{
    int rc;
    
    el_stack_list_t *new_el;

    printf("Введите %d элементов стека\n", num_add);

    for (int i = 0; i < num_add; i++)
    {
        new_el = malloc(sizeof(el_stack_list_t));

        if (!new_el)
        {
            puts(r"Ошибка: не удалось выделить память"w);
            return ERROR_MEMORY;
        }
        
        if ((rc = read_new_el(&new_el->el)))
        {
            free(new_el);
            return rc;
        }

        if (*el_stack_list == NULL)
            new_el->num_el = 1;
        else
            new_el->num_el = (*el_stack_list)->num_el + 1;
        
        new_el->next = *el_stack_list;
        *el_stack_list = new_el;
    }
    
    return EXIT_SUCCESS;
}

int add_stack_list_random(el_stack_list_t **el_stack_list, int num_add)
{
    el_stack_list_t *new_el;

    srand(time(NULL));
    char array_possible_symbol[] = {'(', ')', '[', ']', '{', '}', '0', '1', '+', '-'};

    for (int i = 0; i < num_add; i++)
    {
        new_el = malloc(sizeof(el_stack_list_t));

        if (!new_el)
        {
            puts(r"Ошибка: не удалось выделить память"w);
            return ERROR_MEMORY;
        }

        new_el->el = array_possible_symbol[rand() % 10];

        if (*el_stack_list == NULL)
            new_el->num_el = 1;
        else
            new_el->num_el = (*el_stack_list)->num_el + 1;
        
        new_el->next = *el_stack_list;
        *el_stack_list = new_el;
    }

    return EXIT_SUCCESS;
}

int add_addresses(array_free_areas_t *array, int num_remove, el_stack_list_t *el_stack_list)
{
    el_stack_list_t **p;

    for (int i = 0; i < num_remove; i++)
    {
        p = realloc(array->array, (array->size + 1) * sizeof(el_stack_list_t*));

        if (!p)
        {
            free(array->array);
            puts(r"Ошибка: не удалось выделить память"w);
            return ERROR_MEMORY;
        }

        array->array = p;
        array->array[array->size] = el_stack_list;
        array->size++;
        el_stack_list = el_stack_list->next;
    }

    return EXIT_SUCCESS;
}

void remove_stack_list(el_stack_list_t **el_stack_list, int num_remove)
{
    el_stack_list_t *new_el;

    for (int i = 0; i < num_remove; i++)
    {
        new_el = (*el_stack_list)->next;
        free(*el_stack_list);
        *el_stack_list = new_el;
    }
}

void check_brackets_list(el_stack_list_t **el_stack_list)
{
    el_stack_list_t *new_el;
    
    int flag_round = 0, flag_square = 0, flag_curly = 0;
    
    while (*el_stack_list != NULL)
    {
        new_el = (*el_stack_list)->next;
        
        if ((*el_stack_list)->el == ')')
            flag_round++;
        if ((*el_stack_list)->el == '(' && flag_round != 1)
        {
            flag_round = 1;
            break;
        }
        else if ((*el_stack_list)->el == '(')
            flag_round = 0;
        
        if ((*el_stack_list)->el == ']')
            flag_square++;
        if ((*el_stack_list)->el == '[' && flag_square != 1)
        {
            flag_square = 1;
            break;
        }
        else if ((*el_stack_list)->el == '[')
            flag_square = 0;
        
        if ((*el_stack_list)->el == '}')
            flag_curly++;
        if ((*el_stack_list)->el == '{' && flag_curly != 1)
        {
            flag_curly = 1;
            break;
        }
        else if ((*el_stack_list)->el == '{')
            flag_curly = 0;

        free(*el_stack_list);
        *el_stack_list = new_el;
    }
    
    if (!flag_round && !flag_square && !flag_curly)
        puts(green"Скобки расставлены верно"w);
    else
        puts(red"Скобки расставлены неверно"w);
}