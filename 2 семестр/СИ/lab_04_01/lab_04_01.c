#include <stdio.h>
#include <string.h>

#define OK 0

size_t my_strcspn(const char *str_first, const char *str_second);

void test(const char *str_first, const char *str_second)
{
    int my_len = my_strcspn(str_first, str_second);
    int len = strcspn(str_first, str_second);
    
    if (my_len == len)
    {
        printf("Methods are the same");
    }
    else
    {
        printf("Methods are different");
    }
}

int main(void)
{
    test("", "20");
    test("wertds", "");
    test("s", "s");
    test("0", "5");
    test("52", "135");
    test("52", "531");
    test("25", "135");
    test("25", "531");
    test("231dewsf9", "wer1");
    test("12345", "vnmm");

    return OK;
}
