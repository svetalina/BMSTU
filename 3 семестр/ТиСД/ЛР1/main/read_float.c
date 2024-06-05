#include "head.h"

//Функция принимает заведомо неверную строку вещественного числа
// и уточняет, какие именно произошли ошибки при чтении 
void look_for_mistake_float(char *num)
{
    int i = 1, count_point = 0;
    
    if (strlen(num) == 0)
    {
        puts(r"Ошибка: Пустой ввод вещественного числа"w);
        return;
    }
    
    if (num[0] != '+' && num[0] != '-')
    {
        puts(y"Предупреждение: Отсутсвует знак мантиссы"w);
        i = 0;  
    }
    
    while (num[i] != 'e' && num[i] != 'E' && num[i] != '\n')
    {
        if ((num[i] < '0' || num[i] > '9') && num[i] != '.')
        {
            puts(r"Ошибка: В мантиссе встречены неверные символы"w);
            return;
        }
        
        if (num[i] == '.' && count_point++ != 0)
        {
            puts(r"Ошибка: В мантиссе более, чем одна точка"w);
            return;
        }
        
        if (i++ > MANTISSA_MAX_LEN)
        {
            puts(r"Ошибка: Мантисса слишком длинная"w);
            return;
        }
    }

    if (num[i] != 'e' && num[i] != 'E')
        puts(y"Предупреждение: Отсутсвует экспоненциальная часть"w);
    
    if (num[i++] == '\n')
        return;
    
    if (num[i] != '+' && num[i] != '-')
    {
        puts(y"Предупреждение: Отсутсвует знак порядка"w);
        i++;  
    }
    
    if (num[i] == '\n')
        return;
    
    while (num[i] != '\n')
    {
        if (num[i] < '0' || num[i] > '9')
        {
            puts(r"Ошибка: В порядке встречены неверные символы"w);
            return;
        }
        
        if (i++ > 5)
        {
            puts(r"Ошибка: Порядок слишком длинный"w);
            return;
        }
    }   
}

//Функция принимает заведомо верную строку вещественного числа
// и разбивает ее на поля структуры, которую также принимает на вход
void do_struct(float_number_t *number, char *num)
{
    int i = 0, j = 0, find_point = 1;
    
    if (num[i] == '+' || num[i] == '-')
        number->mantis_sign = num[i++];

    while (num[i] != 'e' && num[i] != 'E' && num[i] != '\0')
    {
        if (num[i] == '.')
        {
            number->point_place = j;
            find_point = 0;
        }
        else
            number->mantissa[j++] = num[i];
    
        i++;
    }
    
    if (find_point)
        number->point_place = j;
      
    if (num[i++] == '\0')
        return;
    
    if (num[i] == '+' || num[i] == '-')
        number->eps_sign = num[i++];
    
    j = 0;

    while (num[i] != '\0')
        number->eps_num[j++] = num[i++];  
}

//Функция читает из птока ввода строку, содержащуюю вещественное число,
//и проверяет ее корректность (принимает ссылку на структуру для числа)
short int read_float(float_number_t *number)
{
    printf("Введите вещественное число:  ");
    
    char num[SIZE_STRING_FLOAT];
    
    gets(num);

    regex_t preg;
    int err;
    regcomp(&preg, PATTERN, REG_EXTENDED);
 
    regmatch_t pm;
    err = regexec(&preg, num, 0, &pm, 0);
        
    if (err != 0) 
    {
        puts(r"Ошибка: Введенная строка противоречит правилам программы"w);
        printf("\n");
        puts("Уточненные ошибки:");
        look_for_mistake_float(num);
        return PATTERN_ERROR;
    }
    
   do_struct(number, num);
    
    return OK;
}
