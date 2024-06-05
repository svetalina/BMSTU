#include "check_addition.h"
#include "check_multiplication.h"
#include "check_inversion.h"

#define ERROR_SIZES -1
#define ERROR_MATCH -2

int comparison_of_matrices(matrix_t *const mtr_1, matrix_t *const mtr_2)
{
    double eps = 1e-5;
    
    if (mtr_1->i_size != mtr_2->i_size  ||
        mtr_1->j_size != mtr_2->j_size)
        return ERROR_SIZES;
    
    for (int i = 0; i < mtr_1->i_size; i++)
        for (int j = 0; j < mtr_1->j_size; j++)
            if (fabs(mtr_1->mtr[i][j] - mtr_2->mtr[i][j]) > eps)
                return ERROR_MATCH;
            
    return EXIT_SUCCESS;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = addition_suite(s);
    s = multiplication_suite(s);
    s = inversion_suite(s);

    return s;
}

int main(void)
{
    Suite *s = tests_suite();
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);

    int error = srunner_ntests_failed(runner);
    srunner_free(runner);

    return error;
}