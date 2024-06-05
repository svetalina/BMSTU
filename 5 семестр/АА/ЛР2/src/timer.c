#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "multiply_matrix.h"

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

void count_time()
{
	TIMER_INIT;
	
    int size_mat[] = {50, 100, 200, 300};

    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < 4; ++i) {
			matrix_t *m1 = create_matrix(size_mat[i] + p, size_mat[i] + p), *m2 = create_matrix(size_mat[i] + p, size_mat[i] + p);
            
			printf("Время для матрицы из %d элементов:\n", size_mat[i] + p);
				
			printf("Стандартный алгоритм: ");
            TIMER_START;
            for (int k = 0; k < COUNT; ++k) {
                matrix_t *res = mul_matrix_def(m1, m2);
                free_matrix(res);
            }
            TIMER_STOP;
			puts("");
			
			printf("Алгоритм Копперсмита-Винограда: ");
            TIMER_START;
            for (int k = 0; k < COUNT; ++k) {
                matrix_t *res = mul_matrix_vinograd(m1, m2);
                free_matrix(res);
            }
            TIMER_STOP;
			puts("");
			
			printf("Оптимизированный алгоритм Копперсмита-Винограда: ");
            TIMER_START;
            for (int k = 0; k < COUNT; ++k) {
                matrix_t *res = mul_matrix_vinograd_opt(m1, m2);
                free_matrix(res);
            }
            TIMER_STOP;
			puts("");

            free_matrix(m1);
            free_matrix(m2);

            puts("");
        }
    }
}
