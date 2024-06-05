#include "head.h"

//Функция выводит нормализированный результат
//(список параметров аналогичен функции умножения)
void print_result(float_number_t num1, int_number_t num2, int *result, int res_power, int ind, int end_ind)
{
    printf(g"Результат умножения чисел: ");
    
    if (num1.mantis_sign != num2.sign)
        printf("-");
    else
        printf("+");
    
    printf("0.");
    
    int count = 0;
    
    while (result[ind] == 0 && ind != MANTISSA_MAX_LEN)
    {
        ind++;
        count++;
        res_power--;
    }
    
    while (result[end_ind] == 0 && end_ind != 0)
        end_ind--;
    
    if (end_ind == 0 && ind == MANTISSA_MAX_LEN * 2)
    {
        printf("0");
        res_power += count;
    }
    
    for (int i = ind; i <= end_ind; i++)
        printf("%d", result[i]);
     
    printf("E");
    
    if (res_power < 0)
        printf("%d", res_power);
    else
        printf("+%d", res_power);        
}
