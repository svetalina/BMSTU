#include "head.h"

int read_general_action(int *general_action)
{
	print_general_menu();
	puts("Введите номер команды: ");
	
    if (scanf("%d", general_action) != 1)
    {
        puts(r"Встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    
    if ( *general_action < 0 || *general_action > 2)
    {
        puts(r"Некорректный номер команды"w);
        return ERROR_GENERAL_ACTION;
    }

    return EXIT_SUCCESS;
}

int read_menu_action(int *menu_action)
{
    print_menu();
    puts("Введите номер команды: ");
    
    if (scanf("%d", menu_action) != 1)
    {
        puts(r"Встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }
    
    if (*menu_action < 0 || *menu_action > 6)
    {
        puts(r"Некорректный номер команды"w);
        return ERROR_MENU_ACTION;
    }
    
    return EXIT_SUCCESS;
}

int read_add_num(int *add_num, int size)
{
    if (size == MAXIMUM_TURN_SIZE)
    {
        puts(r"Очередь переполнена"w);
        return ERROR_OVERFLOW;
    }

    printf("Введите количество добавляемых элементов: ");
    if (scanf("%d", add_num) != 1)
    {
        puts(r"Встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }

    if (*add_num < 0)
    {
        printf("Количество добавляемых элементов не может быть отрицательным");
        return ERROR_ADD_NUM;
    }
    
	if (size + *add_num > MAXIMUM_TURN_SIZE)
    {
        puts(r"В результате добавления такого числа элементов произойдет переполнение очереди"w);
        return ERROR_ADD_NUM;
    }

    return EXIT_SUCCESS;
}

int read_new_elem(int *new_elem)
{
    if (scanf("%d", new_elem) != 1)
    {
        puts(r"Встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }

    return EXIT_SUCCESS;
}

int read_num_remove(int *num_remove, int size)
{
    if (size == 0)
    {
        puts(r"Очередь пуста"w);
        return ERROR_EMPTY;
    }

    puts("Введите кол-во удаляемых элементов: ");
    if (scanf("%d", num_remove) != 1)
    {
        puts(r"Встречены некорректные символы"w);
        return ERROR_SYMBOLS;
    }

    if (*num_remove < 0)
    {
        puts(r"Количество удаляемых элементов не может быть отрицательным"w);
        return ERROR_NUM_REMOVE;
    }
    
	if (*num_remove > size)
    {
        puts(r"В результате удаления такого числа элементов произойдет выход за нижнюю границу очереди"w);
        return ERROR_NUM_REMOVE;
    }

    return EXIT_SUCCESS;
}