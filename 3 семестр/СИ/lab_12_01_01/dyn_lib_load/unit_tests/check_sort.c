#include "check_sort.h" 

void check_sort(int *array_one, const int len_one, int *array_two, const int len_two)
{
    pmysort(array_one, len_one, sizeof(int), pcompare_int);

    int rc = comparison_of_arrays(array_one, array_two, len_two);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
}

START_TEST(sort_usual)
{
    int array_one[] = {56, 7, 8, -24, 12, 4, -8, 34, 8};
    int array_two[] = {-24, -8, 4, 7, 8, 8, 12, 34, 56};

    check_sort(array_one, 9, array_two, 9);
}
END_TEST

START_TEST(sorted_file)
{
    int array_one[] = {-24, -8, 4, 7, 8, 8, 12, 34, 56};
    int array_two[] = {-24, -8, 4, 7, 8, 8, 12, 34, 56};

    check_sort(array_one, 9, array_two, 9);
}
END_TEST

START_TEST(one_element)
{
    int array_one[] = {-24};
    int array_two[] = {-24};

    check_sort(array_one, 1, array_two, 1);
}
END_TEST

START_TEST(sorted_reverse_file)
{
    int array1[] = {56, 34, 12, 8, 8, 7, 4, -8, -24};
    int array2[] = {-24, -8, 4, 7, 8, 8, 12, 34, 56};
 
    check_sort(array1, 9, array2, 9);
}
END_TEST

Suite *sort_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, sort_usual);
    tcase_add_test(tcase_pos, sorted_file);
    tcase_add_test(tcase_pos, one_element);
    tcase_add_test(tcase_pos, sorted_reverse_file);

    suite_add_tcase(s, tcase_pos);

    return s;
}