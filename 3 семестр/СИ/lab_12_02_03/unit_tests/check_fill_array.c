#include "check_fill_array.h"

void check_fill_array(int *arr, int *arr_res, int size)
{
	fill_array(arr, size);
	
    int rc = compare_arrays(arr, size, arr_res, size);
	ck_assert_int_eq(rc, 0);
}

START_TEST(usual_fill_array)
{ 
	int arr[4];
	int arr_res[4] = {2, 3, 5, 7};
	
	check_fill_array(arr, arr_res, 4);
}
END_TEST

START_TEST(one_fill_array)
{ 
	int arr[1];
	int arr_res[1] = {2};
	
	check_fill_array(arr, arr_res, 1);
}
END_TEST


Suite *fill_array_suite(Suite *s)
{
    TCase *tcase_turn;
    tcase_turn = tcase_create("turns");

    tcase_add_test(tcase_turn, usual_fill_array);
	tcase_add_test(tcase_turn, one_fill_array);
	
    suite_add_tcase(s, tcase_turn);
    return s;
}