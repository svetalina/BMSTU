#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "levinstain.h"

#define COUNT 50

#define MICRO 1000000

#define TIMER_INIT \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER t1,t2; \
    double elapsedTime; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&t1);

#define TIMER_STOP \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart/COUNT*MICRO; \
    printf("%lf", elapsedTime);

void count_time(void)
{
    char *arr[10] = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"};
	
	TIMER_INIT;
	
    for (int i = 0; i < 10; ++i)
    {
        printf("\nПолученное время для слова из %d символов:\n", i + 1);

        printf("Метод поиска Левенштейна: ");
		TIMER_START;
        for (int j = 0; j < COUNT; ++j)
            lev(arr[i], arr[i], 0);
        TIMER_STOP;
		puts("");
		
		printf("Нерекурсивный метод поиска Дамерау-Левенштейна: ");
        TIMER_START;
        for (int j = 0; j < COUNT; ++j)
            dameray_lev(arr[i], arr[i], 0);
        TIMER_STOP;
		puts("");
		
		
		printf("Рекурсивный метод поиска Дамерау-Левенштейна: ");
		TIMER_START;
		for (int j = 0; j < COUNT; j++) {
			dameray_lev_rec(arr[i], arr[i], strlen(arr[i]), strlen(arr[i]));
		}
		TIMER_STOP;
        puts("");
		
		
		printf("Рекурсивный с кешированием метод поиска Дамерау-Левенштейна: ");
		TIMER_START;
		for (int j = 0; j < COUNT; j++) {
			dameray_lev_rec_hash(arr[i], arr[i]);
		}
		TIMER_STOP;
		puts("");
    }
}