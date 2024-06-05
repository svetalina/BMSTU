#include "list.h"

int read_list(list_t *list, int unzero_size)
{
    int num, pos;

    while (unzero_size-- > 0)
    {
        puts("Введите элемент вектора-строки: ");
        if (scanf("%d", &num) != 1)
        {
            puts(r"Ошибка: элемент вектора введён неверно"w);
            return ERROR_ELEMENT;
        }

        puts("Введите позицию элемента в векторе-строке (нумерация с 0):");
        if ((scanf("%d", &pos) != 1) || (pos < 0) || (pos > list->size))
        {
            puts(r"Ошибка: позиция элемента вектора введена неверно"w);
            return ERROR_Y_POS;
        }

        list->arr[pos] = num;
    }

    return EXIT_SUCCESS;
}

void random_list(list_t *list, int unzero_size)
{
    srand(time(NULL));

    int pos;

    while (unzero_size-- > 0)
    {
        do
        {
            pos = rand() % list->size;
        } while (list->arr[pos] != 0);
        
        list->arr[pos] = rand() % 100 + 1;
    }
}