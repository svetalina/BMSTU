#include "head.h" 

int read_stack_type(int *stack_type)
{
    printf("Введите чиcло, если хотите:\n"
           "1 - реализовать стек с помощью массива\n"
           "2 - реализовать стек с помощью списка\n"
           "3 - сравнить обе реализации по памяти и времени\n");

    if (scanf("%d", stack_type) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    if (*stack_type < 1 || *stack_type > 3)
    {
        puts(r"Ошибка: введен некорректный номер команды"w);
        return ERROR_STACK_TYPE;
    }

    return EXIT_SUCCESS;
}

int read_action_type(int *action_type)
{
    printf("Ведите число, если хотите:\n"
        "1 - Добавить элементы в стек\n"
        "2 - Добавить случайные элементы в стек\n"
        "3 - Удалить элементы из стека\n"
        "4 - Вывести текущее состояние стека\n"
        "5 - Проверить правильность расстановки скобок в выражении\n"
        "0 - Выйти из программы\n");
    
    if (scanf("%d", action_type) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    
    if (*action_type < 0 || *action_type > 5)
    {
        puts(r"Ошибка: введен некорректный номер команды"w);
        return ERROR_ACTION_TYPE;
    }
    
    return EXIT_SUCCESS;
}

int read_new_el(char *new_elem)
{  
    getchar();
    if (scanf("%c", new_elem) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }

    return EXIT_SUCCESS;
}

int read_num_to_add_stack_array(int *num_add, int size)
{  
    if (size == MAX_STACK_SIZE)
    {
        puts(y"Ошибка: стек переполнен"w);
        return ERROR_STACK_OVERLOW;
    }

    puts("Введите количество добавляемых элементов: ");
    
    if (scanf("%d", num_add) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    if (*num_add < 0)
    {
        puts(r"Ошибка: введенное число не является натуральным"w);
        return ERROR_NUM_ADD;
    }
    if (size + *num_add > MAX_STACK_SIZE)
    {
        puts(r"Ошибка: при добавлении такого числа элементов произойдет переполнение стека"w);
        return ERROR_NUM_ADD;
    }

    return EXIT_SUCCESS;
}

int read_num_to_remove_stack_array(int *num_remove, int size)
{
    if (size == 0)
    {
        puts(r"Ошибка: cтек пуст"w);
        return ERROR_STACK_EMPTY;
    }

    puts("Введите количество удаляемых элементов: ");

    if (scanf("%d", num_remove) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    if (*num_remove < 0)
    {
        puts(r"Ошибка: введенное число не является натуральным"w);
        return ERROR_NUM_REMOVE;
    }
    if (*num_remove > size)
    {
        puts(r"Ошибка: при удалении такого числа элементов произойдет выход за нижнюю границу стека"w);
        return ERROR_NUM_REMOVE;
    }

    return EXIT_SUCCESS;
}

int read_num_to_add_stack_list(int *num_add, el_stack_list_t *el_stack_list)
{
    getchar();
    if (el_stack_list != NULL && el_stack_list->num_el == MAX_STACK_SIZE)
    {
        puts(r"Ошибка: стек переполнен");
        return ERROR_STACK_OVERLOW;
    }

    puts("Введите кол-во добавляемых элементов: ");

    if (scanf("%d", num_add) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    if (*num_add < 0)
    {
        puts(r"Ошибка: введенное число не является натуральным"w);
        return ERROR_NUM_ADD;
    }
    if (el_stack_list == NULL && *num_add > MAX_STACK_SIZE)
    {
        puts(r"Ошибка: при добавлении такого числа элементов произойдет переполнение стека"w);
        return ERROR_NUM_ADD;
    }
    if (el_stack_list != NULL && el_stack_list->num_el + *num_add > MAX_STACK_SIZE)
    {
        puts(r"Ошибка: при добавлении такого числа элементов произойдет переполнение стека"w);
        return ERROR_NUM_ADD;
    }

    return EXIT_SUCCESS;
}

int read_num_to_remove_stack_list(int *num_remove, el_stack_list_t *elem_stack_list)
{
    if (elem_stack_list == NULL)
    {
        puts(r"Ошибка: стек пуст"w);
        return ERROR_STACK_EMPTY;
    }

    puts("Введите кол-во удаляемых элементов : ");
    
    if (scanf("%d", num_remove) != 1)
    {
        puts(r"Ошибка: некорректные символы"w);
        return ERROR_SYMBOLS;
    }

    if (*num_remove < 0)
    {
        puts(r"Ошибка: введенное число не является натуральным"w);
        return ERROR_NUM_REMOVE;
    }
    
    if (*num_remove > elem_stack_list->num_el)
    {
        puts(r"Ошибка: при удалении такого числа элементов произойдет выход за нижнюю границу стека"w);
        return ERROR_NUM_REMOVE;
    }

    return EXIT_SUCCESS;
}
