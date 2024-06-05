#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

void *thread_f1(void *fs)
{
    for (char c = 'a'; c <= 'z'; c += 2)
        fprintf((FILE *)fs, "thread 1: %c\n", c);
}

void *thread_f2(void *fs)
{
    for (char c = 'b'; c <= 'z'; c += 2)
        fprintf((FILE *)fs, "thread 2: %c\n", c);
}

int main(void)
{
    FILE *fs[2] = {fopen("s2.txt", "w"), fopen("s2.txt", "w")};
    pthread_t threads[2];
    void *(*thread_funcs[2])(void *) = {thread_f1, thread_f2};

    for (size_t i = 0; i < 2; i++)
        if (pthread_create(&threads[i], NULL, thread_funcs[i], fs[i]) != 0)
            exit(1);

    for (size_t i = 0; i < 2; i++)
        if (pthread_join(threads[i], NULL) != 0)
            exit(1);
    
    fclose(fs[0]);
    fclose(fs[1]);

    return 0;
}
  