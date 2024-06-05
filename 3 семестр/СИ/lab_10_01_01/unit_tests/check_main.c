#include "check_append.h"
#include "check_remove_duplicates.h"
#include "check_sort.h"
#include "check_reverse.h"

#define ERROR_DATA -1
#define ERROR_SIZES -3

int comparison_of_lists(node_t *head_a, node_t *head_b)
{
    while (head_a != NULL && head_b != NULL)
    {
        if (*(int*) head_a->data != *(int*) head_b->data)
            return ERROR_DATA;
        
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

    s = append_suite(s);
	s = remove_duplicates_suite(s);
	s = sort_suite(s);
	s = reverse_suite(s);

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