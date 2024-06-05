#include "check_decomposition.h"
#include "check_sqr.h"
#include "check_mul.h"
#include "check_div.h"

#define ERROR_NUM -1
#define ERROR_POWER -2
#define ERROR_SIZES -3

int comparison_of_lists(node_t *head_a, node_t *head_b)
{
    while (head_a != NULL && head_b != NULL)
    {
        if (head_a->num != head_b->num)
            return ERROR_NUM;
        if (head_a->power != head_b->power)
            return ERROR_POWER;
        
        head_a = head_a->next;
        head_b = head_b->next;
    }
    
    if (head_a != NULL && head_b != NULL)
        return ERROR_SIZES;
            
    return EXIT_SUCCESS;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = decomposition_suite(s);
	s = sqr_suite(s);
	s = mul_suite(s);
	s = div_suite(s);

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