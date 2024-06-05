#include "../inc/processing.h"

#ifndef X87
long double sum_80_bit_nums(volatile long double a, volatile long double b) {
    return a + b;
}

long double mul_80_bit_nums(volatile long double a, volatile long double b) {
    return a * b;
}

long double asm_sum_80_bit_nums(long double a, long double b) {
    long double res = 0;
    __asm__
    (   
        ".intel_syntax noprefix\n\t"
        "fld qword ptr 16[rbp]\n\t"
        "fld qword ptr 32[rbp]\n\t"
        "faddp\n\t"
        "fstp qword ptr -16[rbp]\n\t"
    );
    return res;
}

long double asm_mul_80_bit_nums(long double a, long double b) {
    long double res = 0;
    __asm__(".intel_syntax noprefix\n\t"
            "fld qword ptr 16[rbp]\n\t"
            "fld qword ptr 32[rbp]\n\t"
            "fmulp\n\t"
            "fstp qword ptr -32[rbp]\n\t"
    );
    return res;

}

void print_80_bit_result() {
    long double a = 10e+12;
    long double b = 10e-12;

    printf("Time for %d trying:\n\n", COUNT);
    puts("WITHOUT ASSEMBLY INSERTION");
    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        sum_80_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);


    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        mul_80_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);

}
void asm_print_80_bit_result() {
    puts("ASSEMBLY INSERTION");
    long double a = 10e+12;
    long double b = 10e-12;

    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        asm_sum_80_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);

    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        asm_mul_80_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);
}
#endif

