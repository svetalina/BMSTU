#include "../inc/processing.h"


double sum_64_bit_nums(volatile double a, volatile double b) {
    return a + b;
}

double mul_64_bit_nums(volatile double a, volatile double b) {
    return a * b;
}

double asm_sum_64_bit_nums(double a, double b) {
    double res = 0;
    __asm__(".intel_syntax noprefix\n\t"
            "fld %1\n\t"
            "fld %2\n\t"
            "faddp\n\t"
            "fstp %0\n\t"
    : "=&m"(res)
    : "m"(a),"m"(b)
    );
    return res;
}

double asm_mul_64_bit_nums(double a, double b) {
    double res = 0;
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

void print_64_bit_result() {
    double a = 10e+12;
    double b = 10e-12;

    printf("Time for %d trying:\n\n", COUNT);
    puts("WITHOUT ASSEMBLY INSERTION");
    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        sum_64_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);


    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        asm_mul_64_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);

}
void asm_print_64_bit_result() {
    puts("ASSEMBLY INSERTION");
    double a = 10e+12;
    double b = 10e-12;

    LARGE_INTEGER beg_sum;
	QueryPerformanceCounter(&beg_sum);
    for (int i = 0; i < COUNT; i++) {
        asm_sum_64_bit_nums(a, b);
    }
    LARGE_INTEGER end_sum;
	QueryPerformanceCounter(&end_sum);
    printf("Sum processing %g s\n", (double) (end_sum.QuadPart - beg_sum.QuadPart) / COUNT);

    LARGE_INTEGER beg_mul;
	QueryPerformanceCounter(&beg_mul);
    for (int i = 0; i < COUNT; i++) {
        asm_mul_64_bit_nums(a, b);
    }
    LARGE_INTEGER end_mul;
	QueryPerformanceCounter(&end_mul);
    printf("Mul processing %g s\n", (double) (end_mul.QuadPart - beg_mul.QuadPart) / COUNT);
}

