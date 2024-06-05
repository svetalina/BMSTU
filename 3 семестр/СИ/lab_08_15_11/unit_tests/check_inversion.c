#include "check_inversion.h" 

void check_inversion_pos(matrix_t *const mtr, matrix_t *const res, matrix_t *const mtr_true)
{
    int rc;
    
    rc = matrix_inversion(mtr, res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = comparison_of_matrices(res, mtr_true);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    free(mtr->mtr);
    free(res->mtr);
    free(mtr_true->mtr);
}

void check_inversion_neg(matrix_t *const mtr, matrix_t *const res, int rc_true)
{
    int rc;
    
    rc = matrix_inversion(mtr, res);
    ck_assert_int_eq(rc, rc_true);
}

START_TEST(inversion_usual_one)
{
    matrix_t mtr = {NULL, 3, 3};
    mtr.mtr = allocate_matrix(mtr.i_size, mtr.j_size);
    mtr.mtr[0][0] = 1;
    mtr.mtr[0][1] = -2;
    mtr.mtr[0][2] = 1;
    mtr.mtr[1][0] = 2;
    mtr.mtr[1][1] = 1;
    mtr.mtr[1][2] = -1;
    mtr.mtr[2][0] = 3;
    mtr.mtr[2][1] = 2;
    mtr.mtr[2][2] = -2;
    
    matrix_t mtr_true = {NULL, 3, 3};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 0;
    mtr_true.mtr[0][1] = 2;
    mtr_true.mtr[0][2] = -1;
    mtr_true.mtr[1][0] = -1;
    mtr_true.mtr[1][1] = 5;
    mtr_true.mtr[1][2] = -3;
    mtr_true.mtr[2][0] = -1;
    mtr_true.mtr[2][1] = 8;
    mtr_true.mtr[2][2] = -5;
    
    matrix_t res = {NULL, 3, 3};;
    identity_matrix_create(&mtr, &res);

    check_inversion_pos(&mtr, &res, &mtr_true);
}
END_TEST

START_TEST(inversion_identity)
{
    matrix_t mtr = {NULL, 3, 3};
    mtr.mtr = allocate_matrix(mtr.i_size, mtr.j_size);
    mtr.mtr[0][0] = 1;
    mtr.mtr[0][1] = 0;
    mtr.mtr[0][2] = 0;
    mtr.mtr[1][0] = 0;
    mtr.mtr[1][1] = 1;
    mtr.mtr[1][2] = 0;
    mtr.mtr[2][0] = 0;
    mtr.mtr[2][1] = 0;
    mtr.mtr[2][2] = 1;
    
    matrix_t mtr_true = {NULL, 3, 3};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 1;
    mtr_true.mtr[0][1] = 0;
    mtr_true.mtr[0][2] = 0;
    mtr_true.mtr[1][0] = 0;
    mtr_true.mtr[1][1] = 1;
    mtr_true.mtr[1][2] = 0;
    mtr_true.mtr[2][0] = 0;
    mtr_true.mtr[2][1] = 0;
    mtr_true.mtr[2][2] = 1;
    
    matrix_t res = {NULL, 3, 3};;
    identity_matrix_create(&mtr, &res);

    check_inversion_pos(&mtr, &res, &mtr_true);
}
END_TEST

START_TEST(inversion_degenerate_one)
{
    matrix_t mtr = {NULL, 3, 3};
    mtr.mtr = allocate_matrix(mtr.i_size, mtr.j_size);
    mtr.mtr[0][0] = 1;
    mtr.mtr[0][1] = 2;
    mtr.mtr[0][2] = 3;
    mtr.mtr[1][0] = 2;
    mtr.mtr[1][1] = 4;
    mtr.mtr[1][2] = 6;
    mtr.mtr[2][0] = 1;
    mtr.mtr[2][1] = 2;
    mtr.mtr[2][2] = 3;
      
    matrix_t res = {NULL, 3, 3};;
    identity_matrix_create(&mtr, &res);

    check_inversion_neg(&mtr, &res, ERROR_DEGENERATE_MATRIX);
}
END_TEST

START_TEST(inversion_degenerate_two)
{
    matrix_t mtr = {NULL, 3, 3};
    mtr.mtr = allocate_matrix(mtr.i_size, mtr.j_size);
    mtr.mtr[0][0] = 0;
    mtr.mtr[0][1] = 0;
    mtr.mtr[0][2] = 0;
    mtr.mtr[1][0] = 0;
    mtr.mtr[1][1] = 0;
    mtr.mtr[1][2] = 0;
    mtr.mtr[2][0] = 0;
    mtr.mtr[2][1] = 0;
    mtr.mtr[2][2] = 0;
      
    matrix_t res = {NULL, 3, 3};;
    identity_matrix_create(&mtr, &res);

    check_inversion_neg(&mtr, &res, ERROR_DEGENERATE_MATRIX);
}
END_TEST

Suite *inversion_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, inversion_usual_one);
    tcase_add_test(tcase_pos, inversion_identity);
    
    TCase *tcase_neg;
    tcase_neg = tcase_create("negatives");
    
    tcase_add_test(tcase_neg, inversion_degenerate_one);
    tcase_add_test(tcase_neg, inversion_degenerate_two);

    suite_add_tcase(s, tcase_pos);
    suite_add_tcase(s, tcase_neg);

    return s;
}
