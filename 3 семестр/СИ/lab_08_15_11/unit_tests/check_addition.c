#include "check_addition.h" 

void check_addition(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, matrix_t *const mtr_true)
{
    matrix_addition(mtr_1, mtr_2, res);

    int rc = comparison_of_matrices(res, mtr_true);
    
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    free(mtr_1->mtr);
    free(mtr_2->mtr);
    free(res->mtr);
    free(mtr_true->mtr);
}

START_TEST(addition_usual_one)
{
    matrix_t mtr_1 = {NULL, 3, 2};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = 1;
    mtr_1.mtr[0][1] = 2;
    mtr_1.mtr[1][0] = 3;
    mtr_1.mtr[1][1] = 4;
    mtr_1.mtr[2][0] = 5;
    mtr_1.mtr[2][1] = 6;
    
    matrix_t mtr_2 = {NULL, 3, 2};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = 6;
    mtr_2.mtr[0][1] = 5;
    mtr_2.mtr[1][0] = 4;
    mtr_2.mtr[1][1] = 3;
    mtr_2.mtr[2][0] = 2;
    mtr_2.mtr[2][1] = 1;
    
    matrix_t mtr_true = {NULL, 3, 2};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 7;
    mtr_true.mtr[0][1] = 7;
    mtr_true.mtr[1][0] = 7;
    mtr_true.mtr[1][1] = 7;
    mtr_true.mtr[2][0] = 7;
    mtr_true.mtr[2][1] = 7;
    
    matrix_t res = {NULL, 3, 2};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_addition(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(addition_usual_two)
{
    matrix_t mtr_1 = {NULL, 3, 2};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -1;
    mtr_1.mtr[0][1] = 20;
    mtr_1.mtr[1][0] = 44;
    mtr_1.mtr[1][1] = 2.67;
    mtr_1.mtr[2][0] = 1;
    mtr_1.mtr[2][1] = 89;
    
    matrix_t mtr_2 = {NULL, 3, 2};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = -45;
    mtr_2.mtr[0][1] = 23;
    mtr_2.mtr[1][0] = 8;
    mtr_2.mtr[1][1] = 4.03;
    mtr_2.mtr[2][0] = 15;
    mtr_2.mtr[2][1] = -1;
    
    matrix_t mtr_true = {NULL, 3, 2};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = -46;
    mtr_true.mtr[0][1] = 43;
    mtr_true.mtr[1][0] = 52;
    mtr_true.mtr[1][1] = 6.7;
    mtr_true.mtr[2][0] = 16;
    mtr_true.mtr[2][1] = 88;
    
    matrix_t res = {NULL, 3, 2};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_addition(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(addition_zero)
{
    matrix_t mtr_1 = {NULL, 3, 2};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -1;
    mtr_1.mtr[0][1] = 20;
    mtr_1.mtr[1][0] = 44;
    mtr_1.mtr[1][1] = 2.67;
    mtr_1.mtr[2][0] = 1;
    mtr_1.mtr[2][1] = 89;
    
    matrix_t mtr_2 = {NULL, 3, 2};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = 0;
    mtr_2.mtr[0][1] = 0;
    mtr_2.mtr[1][0] = 0;
    mtr_2.mtr[1][1] = 0;
    mtr_2.mtr[2][0] = 0;
    mtr_2.mtr[2][1] = 0;
    
    matrix_t mtr_true = {NULL, 3, 2};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = -1;
    mtr_true.mtr[0][1] = 20;
    mtr_true.mtr[1][0] = 44;
    mtr_true.mtr[1][1] = 2.67;
    mtr_true.mtr[2][0] = 1;
    mtr_true.mtr[2][1] = 89;
    
    matrix_t res = {NULL, 3, 2};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_addition(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(addition_one_el)
{
    matrix_t mtr_1 = {NULL, 1, 1};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -99;
    
    matrix_t mtr_2 = {NULL, 1, 1};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = -1;
    
    matrix_t mtr_true = {NULL, 1, 1};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = -100;
    
    matrix_t res = {NULL, 1, 1};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_addition(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

Suite *addition_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, addition_usual_one);
    tcase_add_test(tcase_pos, addition_usual_two);
    tcase_add_test(tcase_pos, addition_zero);
    tcase_add_test(tcase_pos, addition_one_el);

    suite_add_tcase(s, tcase_pos);

    return s;
}