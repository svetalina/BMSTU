#include "head.h"

//Функция производит умножение вещественного и целого чисел
//(принимает по порядку два числа в виде структур - вещественное и целое;
//сылку на массив для записи результатов; по ссылке порядок нового числа 
//и индекс первого ненулевого элемента в массиве результатов)
short int mul(float_number_t num1, int_number_t num2, int *result, int *res_power, int *ind, int *end_ind)
{
    int n1 = strlen(num1.mantissa);
    int n2 = strlen(num2.digit_part);
    
    int index = MANTISSA_MAX_LEN * 2 - 1, q;
   
    int num, write, rem = 0;
    
    for (int i = n1 - 1; i >= 0; i--)
    {
        q = index;
        rem = 0;
        
        for (int j = n2 - 1; j >= 0; j--)
        {
            num = (num1.mantissa[i] - '0') * (num2.digit_part[j] - '0') + rem + result[q];
            
            write = num % 10;
            rem = num / 10;
            
            result[q] = write;
            q--;
        }
        
        index--;
        result[q] = rem;
        
    }

    *ind = (result[q] == 0) ? q + 1 : q;
    
    if (*ind < MANTISSA_MAX_LEN)
    {
        *end_ind = *ind + MANTISSA_MAX_LEN - 1;
        
        result[*end_ind] = (result[*end_ind + 1] > 4) ? result[*end_ind] + 1 : result[*end_ind];
        
        while (result[*end_ind] % 10 == 0 && *end_ind != *ind - 1)
        {
            (*end_ind)--;
            result[*end_ind]++;
        }
    }
    
    *res_power = (MANTISSA_MAX_LEN * 2 - *ind) - (n1 - num1.point_place);
    
    if (num1.eps_sign == '-')
        *res_power -= atoi(num1.eps_num);
    else
        *res_power += atoi(num1.eps_num);

    if (*res_power > 99999)
    {
        puts(r"Ошибка: В ходе вычислений происходит переполнение порядка"w);
        return ERR_POWER_OVERFLOW;
    }

    return OK;
}
