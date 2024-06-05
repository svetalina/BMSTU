#include "check_sort.h"

#define ERROR_SIZES -1
#define ERROR_MATCH -2

int comparison_of_array(item_t **array_1, int size_1, item_t **array_true, int size_true)
{
    double eps = 1e-5;
    
    if (size_1 != size_true)
        return ERROR_SIZES;
    
    for (int i = 0; i < size_1; i++)
    {
        if (strcmp((*array_1 + i)->name, (*array_true + i)->name))
            return ERROR_MATCH;
        if (fabs((*array_1 + i)->mass - (*array_true + i)->mass) > eps)
            return ERROR_MATCH;
        if (fabs((*array_1 + i)->volume - (*array_true + i)->volume) > eps)
            return ERROR_MATCH;
    }
            
    return EXIT_SUCCESS;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = sort_suite(s);

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