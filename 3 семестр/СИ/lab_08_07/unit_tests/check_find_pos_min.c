#include "check_find_pos_min.h" 

void check_find_pos_min(matrix_t *const matrix, int pos_true)
{
    int rc = matrix_find_pos_min(matrix);
    ck_assert_int_eq(rc, pos_true);
    
    matrix_free(matrix);
}

START_TEST(find_pos_min_usual_row)
{
    matrix_t matrix = {NULL, 3, 2, 0};;
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    matrix.matrix[2][0] = 5;
    matrix.matrix[2][1] = 6;
    
    int pos_true = 0;

    check_find_pos_min(&matrix, pos_true);
}
END_TEST

START_TEST(find_pos_min_usual_column)
{
    matrix_t matrix = {NULL, 2, 3, 0};
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 6;
    matrix.matrix[0][1] = 5;
    matrix.matrix[0][2] = 4;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 2;
    matrix.matrix[1][2] = 1;
    
    int pos_true = 2;

    check_find_pos_min(&matrix, pos_true);
}
END_TEST

START_TEST(find_pos_min_few_min)
{
    matrix_t matrix = {NULL, 3, 2, 0};
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 2;
    matrix.matrix[0][1] = 1;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    matrix.matrix[2][0] = 1;
    matrix.matrix[2][1] = 6;
    
    int pos_true = 2;

    check_find_pos_min(&matrix, pos_true);
}
END_TEST

Suite *find_pos_min_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, find_pos_min_usual_row);
    tcase_add_test(tcase_pos, find_pos_min_usual_column);
    tcase_add_test(tcase_pos, find_pos_min_few_min);

    suite_add_tcase(s, tcase_pos);

    return s;
}