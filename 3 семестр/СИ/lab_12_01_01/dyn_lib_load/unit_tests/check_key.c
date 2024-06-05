#include "check_key.h"

START_TEST(filter_usual)
{
    int pb_src[] = {56, 7, 8, -24, 12, 4, -8, 34, 8};
    int *pe_src = pb_src + 9;
    int *pb_dst = malloc(6 * sizeof(int));
    int *pe_dst = NULL;
    pkey(pb_src, pe_src, &pb_dst, &pe_dst);

    int res_array[] = {56, 7, 8, -24, 12, 4};
    int len = 6;
    
    int rc = comparison_of_arrays(pb_dst, res_array, len);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free(pb_dst);
}
END_TEST


START_TEST(invalid_pointer_beg_array)
{
    int array[] = {56, 7, 8, -24, 12, 4, -8, 34, 8};
    int *pb_src = NULL;
    int *pe_src = array + 9;
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = pkey(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, ERROR_FILTRATION_DATA);

    free(pb_dst);
}
END_TEST

START_TEST(invalid_pointer_end_array)
{
    int pb_src[] = {56, 7, 8, -24, 12, 4, -8, 34, 8};
    int *pe_src = NULL;
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = pkey(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, ERROR_FILTRATION_DATA);

    free(pb_dst);
}
END_TEST

START_TEST(pe_array_not_less_pb_array)
{
    int pb_src[] = {56, 7, 8, -24, 12, 4, -8, 34, 8};
    int *pe_src = pb_src - 1;
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = pkey(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, ERROR_FILTRATION_DATA);

    free(pb_dst);
}
END_TEST

START_TEST(empty_file_after_filtering)
{
    int pb_src[] = {-8, 3, 2, 1, 9};
    int *pe_src = pb_src + 5;
    int *pb_dst = malloc(1 * sizeof(int));
    int *pe_dst = NULL;

    int rc = pkey(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, ERROR_EMPTY_FILTRATION);

    free(pb_dst);
}
END_TEST

Suite *key_suite(Suite *s)
{
    TCase *tcase_pos, *tcase_neg;

    tcase_pos = tcase_create("positives");
    tcase_add_test(tcase_pos, filter_usual);
    suite_add_tcase(s, tcase_pos);

    tcase_neg = tcase_create("negatives");
    tcase_add_test(tcase_neg, invalid_pointer_beg_array);
    tcase_add_test(tcase_neg, invalid_pointer_end_array);
    tcase_add_test(tcase_neg, pe_array_not_less_pb_array);
    tcase_add_test(tcase_neg, empty_file_after_filtering);
    suite_add_tcase(s, tcase_neg);

    return s;
}