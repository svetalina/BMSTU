#include "check_mul.h"
#include "check_do_square.h"
#include "check_find_pos_min.h"
#include "check_equalization.h"

#define ERROR_SIZES -1
#define ERROR_MATCH -2

int comparison_of_matrices(matrix_t *const matrix_one, matrix_t *const matrix_two)
{
    if (matrix_one->num_row != matrix_two->num_row  ||
        matrix_one->num_column != matrix_two->num_column)
        return ERROR_SIZES;
    
    for (int i = 0; i < matrix_one->num_row; i++)
        for (int j = 0; j < matrix_one->num_column; j++)
            if (matrix_one->matrix[i][j] != matrix_two->matrix[i][j])
                return ERROR_MATCH;

    return EXIT_SUCCESS;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = mul_suite(s);
    s = do_square_suite(s);
    s = find_pos_min_suite(s);
    s = equalization_suite(s);

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