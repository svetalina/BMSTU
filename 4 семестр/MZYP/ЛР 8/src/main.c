#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100
#define OK 0

void strcopy(char *dest, char *src, int len);

size_t asm_strlen(const char *str)
{
    size_t len = 0;

    __asm__(    
        "mov $0, %%al\n\t"
        "mov %1, %%rdi\n\t"
        "mov $-1, %%rcx\n\t"
        "repne scasb\n\t"
        "neg %%rcx\n\t"
        "sub $2, %%rcx\n\t"
        "mov %%rcx, %0\n\t"
        : "=r"(len)
        : "r"(str)
        : "%rcx", "%rdi", "%al"
        );

    return len;
}

void test_strlen()
{
    const char *test_str = "TeSt StRiNg!";

    printf("\nПодсчёт длины строки: %s\n\nasm_strlen: %lu\nstrlen: %lu\n",
            test_str, asm_strlen(test_str), strlen(test_str));
}

void test_strcopy()
{   
    printf("\nТест strcopy:\n");

    char src[] = "HeLlOw WoRlD!";
    char dest[BUFFER] = "1234567890";
    int len, i_s, i_d;

    len = 2;
    i_s = 0;
    i_d = 0;                                     
    printf("\nsource      - \t%s\ndestination - \t%s\nlength      - \t%d\n"
             "index_src   - \t%d\nindex_dest  - \t%d\n", src, dest, len, i_s, i_d);
    strcopy(dest + i_d, src + i_s, len);
    printf("result      - \t%s\n", dest);

    len = 6;
    i_s = 4;
    i_d = 0;
    printf("\nsource      - \t%s\ndestination - \t%s\nlength      - \t%d\n"
             "index_src   - \t%d\nindex_dest  - \t%d\n", src, dest, len, i_s, i_d);
    strcopy(dest + i_d, src + i_s, len);
    printf("result      - \t%s\n", dest);

    len = 6;
    i_s = 0;
    i_d = 4;
    printf("\nsource      - \t%s\ndestination - \t%s\nlength      - \t%d\n"
             "index_src   - \t%d\nindex_dest  - \t%d\n", src, dest, len, i_s, i_d);
    strcopy(dest + i_d, src + i_s, len);
    printf("result      - \t%s\n", dest);

    len = 1;
    i_s = 1;
    i_d = 1;
    printf("\nsource      - \t%s\ndestination - \t%s\nlength      - \t%d\n"
             "index_src   - \t%d\nindex_dest  - \t%d\n", src, dest, len, i_s, i_d);
    strcopy(dest + i_d, src + i_s, len);
    printf("result      - \t%s\n\n", dest);
}

int main()
{
    test_strlen();
    test_strcopy();

    return OK;
}
