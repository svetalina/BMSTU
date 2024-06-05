#include <stdio.h>

#include "error.h"

int error_handler(int error_code)
{
	switch(error_code)
	{
		case ERROR_READ_ACTION:
			puts("Введенный номер действия не является целым числом от 0 до 4");
			break;
		case ERROR_READ_ROW:
			puts("Введенное количество строк не является целым положительным числом");
			break;
		case ERROR_READ_COL:
			puts("Введенное количество столбцов не является целым положительным числом");
			break;
		case ERROR_READ_ELEM:
			puts("Введенный элемент не является целым числом");
			break;
		default:
			puts("Неизвестная ошибка");
			break;
	}
	
	return error_code;
}