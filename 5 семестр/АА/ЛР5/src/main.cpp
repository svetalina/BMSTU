#include <cstdio>
#include <cstdlib>
#include <time.h>

#include "conveyor.h"

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	
	int a, d, n;
	puts("Введите параметры для создания матрицы \nn - размер матрицы, \na - основание элементов, \nd - корректировка элементов (a +/- da):");
	if(!(scanf("%d %d %d", &n, &a, &d)))
	{
		puts("Ошибка ввода");
		return 1;
	}
	
	int i = 5;
	//for (int i = 90; i <= 100; i += 10)
	//{
		//printf("Количество заявок: %d\n", i);
		linear_processing(i, n, a, d);
		conveyor_processing(i, n, a, d);
	//}
	
	return 0;
}
