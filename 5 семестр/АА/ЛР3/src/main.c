#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"
#include "timer.h"

void print_menu()
{
    printf("\n\nВыберите действие:\n"
           "1) Отсортировать массив\n"
           "2) Сравненить время работы сортировок\n"
           "3) Выход\n");
}

int main(void)
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	
    int action = 0;
	while (action != 3)
	{
		print_menu();
		
        if ((scanf("%d", &action) != 1) || (action < 0 || action > 3))
		{
            puts("Введен невозможный номер меню");
			return EXIT_FAILURE;
		}
		
		if (action == 1)
			sort_array();
		else if (action == 2)
			count_time();
    }

    return EXIT_SUCCESS;
}