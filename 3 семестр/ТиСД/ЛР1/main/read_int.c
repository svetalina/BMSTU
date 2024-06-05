#include "head.h"

//Функция проводит всю первичную обработку целого числа
//(читает, проверяет корректность и разбивает на поля)
short int read_int(int_number_t *number)
{
    printf("Введите целое число:         ");
    
    char num[SIZE_STRING_INT];    
    
    gets(num);
    
    if (strlen(num) == 0)
    {
        puts(r"Ошибка: Пустой ввод целого числа"w);
        return READ_ERROR;
    }
    
    int i = 0, j = 0;
    
    if (num[i] == '+' || num[i] == '-')
            number->sign = num[i++];
    
    for (; i < strlen(num); i++)
    {
        if (num[i] < '0' || num[i] > '9')
        {
            puts(r"Ошибка: Встречены некорректные символы в записи целого числа"w);
            return READ_ERROR; 
        }
        else
            number->digit_part[j++] = num[i];
        
        if (i > MANTISSA_MAX_LEN)
        {
            puts(r"Ошибка: Целое число слишком длинное"w);
            return READ_ERROR;
        }
    }
    
    return OK;
}
