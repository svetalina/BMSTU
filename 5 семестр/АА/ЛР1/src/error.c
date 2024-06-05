#include <stdio.h>

#include "error.h"

int error_handler(int error_code)
{
	switch(error_code)
	{
		case ERROR_READ_ACTION:
			puts("Введенный номер действия не является целым числом от 0 до 5");
			break;
		case ERROR_WORD_1:
			puts("Первое слово введено некорректно");
			break;
		case ERROR_WORD_2:
			puts("Второе слово введено некорректнл");
			break;
		default:
			puts("Неизвестная ошибка");
			break;
	}
	
	return error_code;
}