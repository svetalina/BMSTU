#include "../inc/check_key.h"
#include "../inc/check_sort.h"

#define  ERROR_MATCH -1

int comparison_of_arrays(int *array_one, int *array_two, int len)
{
    for (int i = 0; i < len; i++)
        if (array_one[i] != array_two[i])
            return ERROR_MATCH;

    return EXIT_SUCCESS;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = sort_suite(s);
    s = key_suite(s);

    return s;
}

int main(void)
{
    Suite *s = tests_suite();
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);

    int error = srunner_ntests_failed(runner);
    srunner_free(runner);

    return error;
}