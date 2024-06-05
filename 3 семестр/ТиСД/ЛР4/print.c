#include "head.h" 

void print_stack_array(stack_array_t *stack_array)
{
    printf("Текущий размер стека - %d\n", stack_array->size);

    char *p = stack_array->ptr;
    for (int i = stack_array->size; i > 0; i--)
        printf("%c ", *(p--));
        
    puts("");
}

void print_stack_list(el_stack_list_t **el_stack_list)
{
    if (*el_stack_list == NULL)
    {
        puts("Текущий размер стека - 0");
        return;
    }
    else
        printf("Текущий размер стека - %d\n", (*el_stack_list)->num_el);
    
    el_stack_list_t *p = *el_stack_list;

    while (p != NULL)
    {
        printf("%-10c %p\n", p->el, (void *)p);
        p = p->next;
    }
}

void print_array(array_free_areas_t *array)
{
    puts("Массив адресов освобождённых элементов стека: ");
    
    if (array->size == 0)
        puts("Массив пуст");

    for (int i = 0; i < array->size; i++)
        printf("%p\n", (void *)array->array[i]);

}