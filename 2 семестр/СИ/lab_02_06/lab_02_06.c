#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define MIN_CONST 1000
#define OK 0

int process_1(const int *b, const int nb)
{
    int min = MIN_CONST;

    for(int i = 1; i < nb; ++i)
    {
       if(b[i - 1] * b[i] < min)
       {
           min = b[i - 1] * b[i];
       }
    }

    return min;
}

int process_2(const int *b, const int nb)
{
    int min = MIN_CONST;

    for(int i = 1; i < nb; ++i)
    {
       if(*(b + i - 1) * *(b + i) < min)
       {
           min = *(b + i - 1) * *(b + i);
       }
    }
    
    return min;
}

int process_3(int *pa, const int *pb)
{
    int min = MIN_CONST;

    while(pa != pb)
    {
       if(*(pa) * *(pa + 1) < min)
       {
          min = *(pa) * *(pa + 1);
       }
       pa += 1;
    }

    return min;
}

void time_process_1(const int N, const int size, int *array)
{
    struct timeval tv_start, tv_stop;
    int64_t sum = 0;
    
    for(int i = 0; i < N; i++)
    {
       gettimeofday(&tv_start, NULL);
       process_1(array, size);
       gettimeofday(&tv_stop, NULL);
       sum += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + \
       (tv_stop.tv_usec - tv_start.tv_usec);
    }
    printf("%" PRId64 " us\n", sum / N);
    
}

void time_process_2(const int N, const int size, int *array)
{
    struct timeval tv_start, tv_stop;
    int64_t sum = 0;
    
    for(int i = 0; i < N; i++)
    {
       gettimeofday(&tv_start, NULL);
       process_2(array, size);
       gettimeofday(&tv_stop, NULL);
       sum += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + \
       (tv_stop.tv_usec - tv_start.tv_usec);
    }
    printf("%" PRId64 " us\n", sum / N);
}

void time_process_3(const int N, const int size, int *array)
{
    struct timeval tv_start, tv_stop;
    int64_t sum = 0;
    
    int *p_start, *p_end;
    p_start = &array[0];
    p_end = &array[size - 1];

    for(int i = 0; i < N; i++)
    {
       gettimeofday(&tv_start, NULL);
       process_3(p_start, p_end);
       gettimeofday(&tv_stop, NULL);
       sum += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + \
       (tv_stop.tv_usec - tv_start.tv_usec);
    }
    printf("%" PRId64 " us\n", sum / N);
}

int main(void)
{
    int N, size;
    int array[MAX_SIZE];

    scanf("%d", &N);
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
    }
    
    time_process_1(N, size, array);
    time_process_2(N, size, array);
    time_process_3(N, size, array);

    return OK;
}
