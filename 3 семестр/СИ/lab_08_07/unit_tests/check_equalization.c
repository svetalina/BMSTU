#include "check_equalization.h" 

void check_equalization(matrix_t *const matrix, int diff, matrix_t *const matrix_true)
{
    matrix_equalization(matrix, diff);

    int rc = comparison_of_matrices(matrix, matrix_true);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    matrix_free(matrix);
    matrix_free(matrix_true);
}

START_TEST(equalization_usual)
{
    matrix_t matrix = {NULL, 3, 3, 0};
    matrix_allocate(&matrix);
    matrix.num_row = 2;
    matrix.num_column = 2;
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    
    int diff = 1;
    
    matrix_t matrix_true = {NULL, 3, 3, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 1;
    matrix_true.matrix[0][1] = 2;
    matrix_true.matrix[0][2] = 2;
    matrix_true.matrix[1][0] = 3;
    matrix_true.matrix[1][1] = 4;
    matrix_true.matrix[1][2] = 4;
    matrix_true.matrix[2][0] = 1;
    matrix_true.matrix[2][1] = 2;
    matrix_true.matrix[2][2] = 2;

    check_equalization(&matrix, diff, &matrix_true);
}
END_TEST

START_TEST(equalization_one_el)
{
    matrix_t matrix = {NULL, 3, 3, 0};
    matrix_allocate(&matrix);
    matrix.num_row = 1;
    matrix.num_column = 1;
    matrix.matrix[0][0] = 5;
    
    int diff = 2;
    
    matrix_t matrix_true = {NULL, 3, 3, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 5;
    matrix_true.matrix[0][1] = 5;
    matrix_true.matrix[0][2] = 5;
    matrix_true.matrix[1][0] = 5;
    matrix_true.matrix[1][1] = 5;
    matrix_true.matrix[1][2] = 5;
    matrix_true.matrix[2][0] = 5;
    matrix_true.matrix[2][1] = 5;
    matrix_true.matrix[2][2] = 5;

    check_equalization(&matrix, diff, &matrix_true);
}
END_TEST

START_TEST(equalization_unit)
{
    matrix_t matrix = {NULL, 3, 3, 0};
    matrix_allocate(&matrix);
    matrix.num_row = 2;
    matrix.num_column = 2;
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 0;
    matrix.matrix[1][0] = 0;
    matrix.matrix[1][1] = 1;
    
    int diff = 1;
    
    matrix_t matrix_true = {NULL, 3, 3, 0};
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 1;
    matrix_true.matrix[0][1] = 0;
    matrix_true.matrix[0][2] = 1;
    matrix_true.matrix[1][0] = 0;
    matrix_true.matrix[1][1] = 1;
    matrix_true.matrix[1][2] = 1;
    matrix_true.matrix[2][0] = 0;
    matrix_true.matrix[2][1] = 0;
    matrix_true.matrix[2][2] = 0;

    check_equalization(&matrix, diff, &matrix_true);
}
END_TEST

Suite *equalization_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, equalization_usual);
    tcase_add_test(tcase_pos, equalization_one_el);
    tcase_add_test(tcase_pos, equalization_unit);

    suite_add_tcase(s, tcase_pos);

    return s;
}