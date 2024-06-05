#include "head.h"

void print_general_menu(void)
{
    printf("1. Cравнить работы реализаций очередей (списка и массива) по памяти и времени\n"
           "2. Решить задачу\n"
           "0. Выйти из программы\n");
}

void print_menu(void)
{
    printf("1. Добавить элементы в очередь\n"
        "2. Добавить случайные элементы в очередь\n"
        "3. Удалить элементы из очереди\n"
        "4. Вывести текущее состояние очереди (массив)\n"
        "5. Вывести текущее состояние очереди (список)\n"
        "6. Вывести массив освобождённых адресов\n"
        "0. Выйти из программы\n");
}

void print_result(int64_t start, int64_t end)
{
    printf(c"%lld тактов, %.10lf секунд\n"w, end - start, (double)(end - start) / HZ);  
}

void print_turn_array(turn_array_t *turn_array)
{
    printf("Текущий размер очереди - %d\n", turn_array->size);
    if (turn_array->size == 0)
        return;

    int *p = turn_array->head;

    printf("HEAD\n");
    while(p > turn_array->tail)
        printf("%d\n", *(p--));
    printf("TAIL\n");
}

void print_turn_list(turn_list_t *list)
{
	printf("Текущий размер очереди - %d\n", list->size);
    if (list->size == 0)
        return;
    
    elem_turn_list_t *p = list->head;

    printf("HEAD\n");
    while (p != NULL)
    {
        printf("%-10d %p\n", p->elem, (void*) p);
        p = p->next;
    }
    printf("TAIL\n");
}


void print_freed_array(array_freed_areas_t *array)
{
    printf("Массив адресов освобождённых элементов очереди:\n");
	
	if (array->size == 0)
		printf("Массив адресов освобождённых элементов очереди пуст\n");

    for (int i = 0; i < array->size; i++)
        printf("%p\n", (void*) array->array[i]);
}