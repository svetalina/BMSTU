#include "check_fill_array.h"
#include "check_fill_array_after_even.h"

#define ERROR_SIZE 1
#define ERROR_ELEMENT 2

int compare_arrays(int *arr_1, int size_1, int *arr_2, int size_2)
{
	if (size_1 != size_2)
		return ERROR_SIZE;
	
	for (int i = 0; i < size_1; i++)
		if (arr_1[i] != arr_2[i])
			return ERROR_ELEMENT;
	
	return EXIT_SUCCESS;
}


Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = fill_array_suite(s);
	s = fill_array_after_even_suite(s);
    
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