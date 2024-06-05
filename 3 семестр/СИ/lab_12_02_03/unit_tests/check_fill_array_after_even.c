#include "check_fill_array.h"

void check_fill_array_after_even(int *arr, int size, int *arr_res, int size_res, int num)
{
	int arr_2[10];
	int size_2 = 10;
	size_2 = fill_array_after_even(arr, size, arr_2, size_2, num);

    int rc = compare_arrays(arr_2, size_2, arr_res, size_res);
	ck_assert_int_eq(rc, 0);
}


START_TEST(usual_fill_array_after_even)
{ 
	int arr[4] = {2, 4, 6, 7};
	int num = 0;
	int arr_res[7] = {2, 0, 4, 0, 6, 0, 7};
	
	check_fill_array_after_even(arr, 4, arr_res, 7,  num);
}
END_TEST

START_TEST(one_fill_array_after_even)
{ 
	int arr[1] = {2};
	int num = 3;
	int arr_res[4] = {2, 3};
	
	check_fill_array_after_even(arr, 1, arr_res, 2,  num);
}
END_TEST

Suite *fill_array_after_even_suite(Suite *s)
{
    TCase *tcase_turn;
    tcase_turn = tcase_create("turns");

    tcase_add_test(tcase_turn, usual_fill_array_after_even);
	tcase_add_test(tcase_turn, one_fill_array_after_even);
	
    suite_add_tcase(s, tcase_turn);
    return s;
}