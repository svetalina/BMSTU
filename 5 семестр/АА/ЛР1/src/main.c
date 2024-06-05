#include <stdlib.h>
#include <stdio.h>

#include "levinstain.h"
#include "timer.h"
#include "error.h"

#define ACTION_MIN 0
#define ACTION_MAX 5

void print_menu(void)
{
    printf("Введите соответствующий номер меню:\n"
           "1. Метод поиска Левенштейна\n"
           "2. Нерекурсивный метод поиска Дамерау-Левенштейна\n"
           "3. Рекурсивный метод поиска Дамерау-Левенштейна\n"
		   "4. Рекурсивный с кешированием метод поиска Дамерау-Левенштейна\n"
		   "5. Замер времени\n"
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
        if (action == 5)
			count_time();
		else
			if (rc = find_distance(action))
				return error_handler(rc);
    }

    return EXIT_SUCCESS;
}