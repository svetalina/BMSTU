#include "check_mul.h" 

void check_mul(matrix_t *const matrix_one, matrix_t *const matrix_two, matrix_t *const matrix_result, matrix_t *const matrix_true)
{
    matrix_mul(matrix_one, matrix_two, matrix_result);

    int rc = comparison_of_matrices(matrix_result, matrix_true);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    matrix_free(matrix_one);
    matrix_free(matrix_two);
    matrix_free(matrix_result);
    matrix_free(matrix_true);
}

START_TEST(mul_usual)
{
    matrix_t matrix_one = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_one);
    matrix_one.matrix[0][0] = 1;
    matrix_one.matrix[0][1] = 2;
    matrix_one.matrix[1][0] = 3;
    matrix_one.matrix[1][1] = 4;
    matrix_one.matrix[2][0] = 5;
    matrix_one.matrix[2][1] = 6;
    
    matrix_t matrix_two = {NULL, 2, 1, 0};
    matrix_allocate(&matrix_two);
    matrix_two.matrix[0][0] = 1;
    matrix_two.matrix[1][0] = 2;
    
    matrix_t matrix_true = {NULL, 3, 1, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 5;
    matrix_true.matrix[1][0] = 11;
    matrix_true.matrix[2][0] = 17;
    
    matrix_t matrix_result = {NULL, 3, 1, 0};;
    matrix_allocate(&matrix_result);

    check_mul(&matrix_one, &matrix_two, &matrix_result, &matrix_true);
}
END_TEST

START_TEST(mul_one_zero_matrix)
{
    matrix_t matrix_one = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_one);
    matrix_one.matrix[0][0] = 0;
    matrix_one.matrix[0][1] = 0;
    matrix_one.matrix[1][0] = 0;
    matrix_one.matrix[1][1] = 0;
    matrix_one.matrix[2][0] = 0;
    matrix_one.matrix[2][1] = 0;
    
    matrix_t matrix_two = {NULL, 2, 1, 0};
    matrix_allocate(&matrix_two);
    matrix_two.matrix[0][0] = 1;
    matrix_two.matrix[1][0] = 2;
    
    matrix_t matrix_true = {NULL, 3, 1, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 0;
    matrix_true.matrix[1][0] = 0;
    matrix_true.matrix[2][0] = 0;
    
    matrix_t matrix_result = {NULL, 3, 1, 0};
    matrix_allocate(&matrix_result);

    check_mul(&matrix_one, &matrix_two, &matrix_result, &matrix_true);
}
END_TEST

START_TEST(mul_two_zero_matrix)
{
    matrix_t matrix_one = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_one);
    matrix_one.matrix[0][0] = 0;
    matrix_one.matrix[0][1] = 0;
    matrix_one.matrix[1][0] = 0;
    matrix_one.matrix[1][1] = 0;
    matrix_one.matrix[2][0] = 0;
    matrix_one.matrix[2][1] = 0;
    
    matrix_t matrix_two = {NULL, 2, 1, 0};
    matrix_allocate(&matrix_two);
    matrix_two.matrix[0][0] = 0;
    matrix_two.matrix[1][0] = 0;
    
    matrix_t matrix_true = {NULL, 3, 1, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 0;
    matrix_true.matrix[1][0] = 0;
    matrix_true.matrix[2][0] = 0;
    
    matrix_t matrix_result = {NULL, 3, 1, 0};
    matrix_allocate(&matrix_result);

    check_mul(&matrix_one, &matrix_two, &matrix_result, &matrix_true);
}
END_TEST

START_TEST(mul_unit_matrix)
{
    matrix_t matrix_one = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_one);
    matrix_one.matrix[0][0] = 1;
    matrix_one.matrix[0][1] = 2;
    matrix_one.matrix[1][0] = 3;
    matrix_one.matrix[1][1] = 4;
    matrix_one.matrix[2][0] = 5;
    matrix_one.matrix[2][1] = 6;
    
    matrix_t matrix_two = {NULL, 2, 2, 0};
    matrix_allocate(&matrix_two);
    matrix_two.matrix[0][0] = 1;
    matrix_two.matrix[0][1] = 0;
    matrix_two.matrix[1][0] = 0;
    matrix_two.matrix[1][1] = 1;
    
    matrix_t matrix_true = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 1;
    matrix_true.matrix[0][1] = 2;
    matrix_true.matrix[1][0] = 3;
    matrix_true.matrix[1][1] = 4;
    matrix_true.matrix[2][0] = 5;
    matrix_true.matrix[2][1] = 6;
    
    matrix_t matrix_result = {NULL, 3, 2, 0};
    matrix_allocate(&matrix_result);

    check_mul(&matrix_one, &matrix_two, &matrix_result, &matrix_true);
}
END_TEST

Suite *mul_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, mul_usual);
    tcase_add_test(tcase_pos, mul_one_zero_matrix);
    tcase_add_test(tcase_pos, mul_two_zero_matrix);
    tcase_add_test(tcase_pos, mul_unit_matrix);

    suite_add_tcase(s, tcase_pos);

    return s;
}