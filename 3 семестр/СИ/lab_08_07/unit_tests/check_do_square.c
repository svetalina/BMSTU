#include "check_do_square.h" 

void check_do_square(matrix_t *const matrix, matrix_t *const matrix_true)
{
    matrix_do_square(matrix);

    int rc = comparison_of_matrices(matrix, matrix_true);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    matrix_free(matrix);
    matrix_free(matrix_true);
}

START_TEST(do_square_usual_row)
{
    matrix_t matrix = { NULL, 3, 2, 0 };
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    matrix.matrix[2][0] = 5;
    matrix.matrix[2][1] = 6;
    
    matrix_t matrix_true = { NULL, 2, 2, 0 };
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 3;
    matrix_true.matrix[0][1] = 4;
    matrix_true.matrix[1][0] = 5;
    matrix_true.matrix[1][1] = 6;

    check_do_square(&matrix, &matrix_true);
}
END_TEST

START_TEST(do_square_usual_column)
{
    matrix_t matrix = { NULL, 2, 3, 0 };
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[0][2] = 3;
    matrix.matrix[1][0] = 4;
    matrix.matrix[1][1] = 5;
    matrix.matrix[1][2] = 6;
    
    matrix_t matrix_true = { NULL, 2, 2, 0 };
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 2;
    matrix_true.matrix[0][1] = 3;
    matrix_true.matrix[1][0] = 5;
    matrix_true.matrix[1][1] = 6;

    check_do_square(&matrix, &matrix_true);
}
END_TEST

START_TEST(do_square_already_square)
{
    matrix_t matrix = { NULL, 2, 2, 0 };
    matrix_allocate(&matrix);
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    
    matrix_t matrix_true = { NULL, 2, 2, 0 };
    matrix_allocate(&matrix_true);
    matrix_true.matrix[0][0] = 1;
    matrix_true.matrix[0][1] = 2;
    matrix_true.matrix[1][0] = 3;
    matrix_true.matrix[1][1] = 4;

    check_do_square(&matrix, &matrix_true);
}
END_TEST

Suite *do_square_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, do_square_usual_row);
    tcase_add_test(tcase_pos, do_square_usual_column);
    tcase_add_test(tcase_pos, do_square_already_square);

    suite_add_tcase(s, tcase_pos);

    return s;
}