#include <time.h>
#include <float.h>
#include "../inc/general.h"

#define COUNT 10000

void print(vector_t *vec) {
    printf("[%lf %lf %lf] ", vec->buf[0], vec->buf[1], vec->buf[2]);
    puts("");
}

void test(size_t count) {
    float a = 10.0;
    float b = 20.0;
    float c = 30.0;
    float res_c = 0;
    float res_asm = 0;

    vector_t vec_a = {a, b, c};
    vector_t vec_b = {a, b, c};

    puts("TEST C");
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);
    for (size_t i = 0; i < count; i++) 
    {
        c_scalar_prod(&res_c, &vec_a, &vec_b);
    }
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
    printf("result = %f\ntime = %.3g s\n", res_c, (double) (end.QuadPart - start.QuadPart) / COUNT);

    puts("\nTEST SSE ASSEMBLY");
    QueryPerformanceCounter(&start);
    for (size_t i = 0; i < count; i++) 
    {
        sse_scalar_prod(&res_asm, &vec_a, &vec_b);
    }
    QueryPerformanceCounter(&end);
    printf("result = %f\ntime = %.3g s\n", res_asm, (double) (end.QuadPart - start.QuadPart) / COUNT);
}

int main() {

    test(COUNT);

    return 0;
}