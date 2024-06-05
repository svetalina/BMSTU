#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"
#include "timer.h"

void print_menu()
{
    printf("\n\nВыберите действие:\n"
           "1) Однопоточный алгоритм Дейкстры\n"
		   "2) Много поточный алгоритм Дейкстры\n"
           "3) Сравненить время работы сортировок\n"
           "4) Выход\n");
}

int main(void)
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	
    int action = 0;
	while (action != 4)
	{
		print_menu();
		
        if ((scanf("%d", &action) != 1) || (action < 0 || action > 4))
		{
            puts("Введен невозможный номер меню");
			return EXIT_FAILURE;
		}
		
		if (action == 1 || action == 2)
			do_algorithm(action);
		else if (action == 3)
			count_time();
    }

    return EXIT_SUCCESS;
}