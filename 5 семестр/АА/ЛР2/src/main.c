#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "multiply_matrix.h"
#include "timer.h"

#define ACTION_MIN 0
#define ACTION_MAX 4

void print_menu(void)
{
    printf("Введите соответствующий номер меню:\n"
           "1. Стандартный алгоритм умножения матриц\n"
           "2. Алгоритм Копперсмита-Винограда\n"
           "3. Оптимизированный алгоритм Копперсмита-Винограда\n"
		   "4. Замер времени\n"
           "0. Выход\n");

}

int main(void)
{
	setbuf(stdout, NULL);
	
    int action, rc;

    while (1)
	{
		print_menu();
        if (scanf("%d", &action) != 1 || action < ACTION_MIN || action  > ACTION_MAX)
            return error_handler(ERROR_READ_ACTION);
		puts("");
		
		if (action == 0)
			break;
        if (action == 4)
			count_time();
		else
			if (rc = multiply_matrix(action))
				return error_handler(rc);
    }

    return EXIT_SUCCESS;
}