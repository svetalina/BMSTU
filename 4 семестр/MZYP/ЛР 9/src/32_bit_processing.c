#include "../inc/processing.h"


float sum_32_bit_nums(volatile float a, volatile float b) {
    return a + b;
}

float mul_32_bit_nums(volatile float a, volatile float b) {
    return a * b;
}

float asm_sum_32_bit_nums(float a, float b) {
    float res = 0;
    __asm__(".intel_syntax noprefix\n\t"
            "fld %1\n\t"                    // загрузить а на вершину стэка
            "fld %2\n\t"                    // загрузить b
            "faddp\n\t"                     // сложить
            "fstp %0\n\t"                   // Сохранить вещественное значение с извлечением из стека (FPU)
            : "=&m"(res)
            : "m"(a),"m"(b)
            );
    return res;
}

float asm_mul_32_bit_nums(float a, float b) {
    float res = 0;
    __asm__(".intel_syntax noprefix\n\t"
            "fld %1\n\t"
            "fld %2\n\t"
            "fmulp\n\t"
            "fstp %0\n\t"
    : "=&m"(res)
    : "m"(a),"m"(b)
    );
    return res;

}

void print_32_bit_result() {
    float a = 10e+12;
    float b = 10e-12;


    printf("Time for %d trying:\n\n", COUNT);
    puts("WITHOUT ASSEMBLY INSERTION");
    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        sum_32_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);


    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        mul_32_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);

}
void asm_print_32_bit_result() {
    puts("ASSEMBLY INSERTION");
    float a = 10e+3;
    float b = 10e-3;

    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        asm_sum_32_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);

    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        asm_mul_32_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);
}

