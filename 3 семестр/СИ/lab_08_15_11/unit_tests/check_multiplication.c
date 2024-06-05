#include "check_multiplication.h" 

void check_multiplication(matrix_t *const mtr_1, matrix_t *const mtr_2, matrix_t *const res, matrix_t *const mtr_true)
{
    matrix_multiplication(mtr_1, mtr_2, res);

    int rc = comparison_of_matrices(res, mtr_true);
    
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    free(mtr_1->mtr);
    free(mtr_2->mtr);
    free(res->mtr);
    free(mtr_true->mtr);
}

START_TEST(multiplication_usual_one)
{
    matrix_t mtr_1 = {NULL, 3, 2};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = 1;
    mtr_1.mtr[0][1] = 2;
    mtr_1.mtr[1][0] = 3;
    mtr_1.mtr[1][1] = 4;
    mtr_1.mtr[2][0] = 5;
    mtr_1.mtr[2][1] = 6;
    
    matrix_t mtr_2 = {NULL, 2, 3};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = 6;
    mtr_2.mtr[0][1] = 5;
    mtr_2.mtr[0][2] = 4;
    mtr_2.mtr[1][0] = 3;
    mtr_2.mtr[1][1] = 2;
    mtr_2.mtr[1][2] = 1;
    
    matrix_t mtr_true = {NULL, 3, 3};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 12;
    mtr_true.mtr[0][1] = 9;
    mtr_true.mtr[0][2] = 6;
    mtr_true.mtr[1][0] = 30;
    mtr_true.mtr[1][1] = 23;
    mtr_true.mtr[1][2] = 16;
    mtr_true.mtr[2][0] = 48;
    mtr_true.mtr[2][1] = 37;
    mtr_true.mtr[2][2] = 26;
    
    matrix_t res = {NULL, 3, 3};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_multiplication(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(multiplication_usual_two)
{
    matrix_t mtr_1 = {NULL, 3, 2};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -1;
    mtr_1.mtr[0][1] = 20;
    mtr_1.mtr[1][0] = 44;
    mtr_1.mtr[1][1] = 2.67;
    mtr_1.mtr[2][0] = 1;
    mtr_1.mtr[2][1] = 89;
    
    matrix_t mtr_2 = {NULL, 2, 3};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = -45;
    mtr_2.mtr[0][1] = 23;
    mtr_2.mtr[0][2] = 8;
    mtr_2.mtr[1][0] = 4.03;
    mtr_2.mtr[1][1] = 15;
    mtr_2.mtr[1][2] = -1;
    
    matrix_t mtr_true = {NULL, 3, 3};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 125.6;
    mtr_true.mtr[0][1] = 277;
    mtr_true.mtr[0][2] = -28;
    mtr_true.mtr[1][0] = -1969.2399;
    mtr_true.mtr[1][1] = 1052.05;
    mtr_true.mtr[1][2] = 349.33;
    mtr_true.mtr[2][0] = 313.67;
    mtr_true.mtr[2][1] = 1358;
    mtr_true.mtr[2][2] = -81;
    
    matrix_t res = {NULL, 3, 3};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_multiplication(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(multiplication_zero)
{
    matrix_t mtr_1 = {NULL, 2, 4};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -1;
    mtr_1.mtr[0][1] = 20;
    mtr_1.mtr[0][2] = 44;
    mtr_1.mtr[0][3] = 2.67;
    mtr_1.mtr[1][0] = -4;
    mtr_1.mtr[1][1] = 59;
    mtr_1.mtr[1][2] = 21;
    mtr_1.mtr[1][3] = 2.9;
    
    matrix_t mtr_2 = {NULL, 4, 1};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = 0;
    mtr_2.mtr[0][1] = 0;
    mtr_2.mtr[0][2] = 0;
    mtr_2.mtr[0][3] = 0;
    
    matrix_t mtr_true = {NULL, 2, 1};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 0;
    mtr_true.mtr[1][0] = 0;
    
    matrix_t res = {NULL, 2, 1};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_multiplication(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

START_TEST(multiplication_one_el)
{
    matrix_t mtr_1 = {NULL, 1, 1};
    mtr_1.mtr = allocate_matrix(mtr_1.i_size, mtr_1.j_size);
    mtr_1.mtr[0][0] = -99;
    
    matrix_t mtr_2 = {NULL, 1, 1};
    mtr_2.mtr = allocate_matrix(mtr_2.i_size, mtr_2.j_size);
    mtr_2.mtr[0][0] = -1;
    
    matrix_t mtr_true = {NULL, 1, 1};
    mtr_true.mtr = allocate_matrix(mtr_true.i_size, mtr_true.j_size);
    mtr_true.mtr[0][0] = 99;
    
    matrix_t res = {NULL, 1, 1};;
    res.mtr = allocate_matrix(res.i_size, res.j_size);

    check_multiplication(&mtr_1, &mtr_2, &res, &mtr_true);
}
END_TEST

Suite *multiplication_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, multiplication_usual_one);
    tcase_add_test(tcase_pos, multiplication_usual_two);
    tcase_add_test(tcase_pos, multiplication_zero);
    tcase_add_test(tcase_pos, multiplication_one_el);

    suite_add_tcase(s, tcase_pos);

    return s;
}
