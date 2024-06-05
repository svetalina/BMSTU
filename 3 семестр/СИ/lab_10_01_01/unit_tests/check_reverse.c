#include "check_reverse.h"

void check_reverse(node_t *head_a, node_t *head_res)
{
    int rc;
       
    head_a = reverse(head_a);

    rc = comparison_of_lists(head_a, head_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    free_list(head_a);
    free_list(head_res);
}

START_TEST(reverse_usual)
{   
    year_t array_a, array_res;
    node_t *head_a = NULL, *head_res = NULL;

    array_a.array = malloc(6 * sizeof(int));
    array_a.size = 6;
    array_a.array[0] = 1984;
    array_a.array[1] = 1983;
    array_a.array[2] = 1988;
    array_a.array[3] = 2002;
    array_a.array[4] = 1989;
    array_a.array[5] = 1930;
    
    fill_list(&head_a, &array_a);
    
    array_res.array = malloc(6 * sizeof(int));
    array_res.size = 6;
    array_res.array[0] = 1930;
    array_res.array[1] = 1989;
    array_res.array[2] = 2002;
    array_res.array[3] = 1988;
    array_res.array[4] = 1983;
    array_res.array[5] = 1984;
    
    fill_list(&head_res, &array_res);

    check_reverse(head_a, head_res);
    
    free(array_a.array);
    free(array_res.array);
}
END_TEST

START_TEST(reverse_one)
{   
    year_t array_a, array_res;
    node_t *head_a = NULL, *head_res = NULL;

    array_a.array = malloc(1 * sizeof(int));
    array_a.size = 1;
    array_a.array[0] = 1984;
    
    fill_list(&head_a, &array_a);
    
    array_res.array = malloc(1 * sizeof(int));
    array_res.size = 1;
    array_res.array[0] = 1984;
    
    fill_list(&head_res, &array_res);

    check_reverse(head_a, head_res);
    
    free(array_a.array);
    free(array_res.array);
}
END_TEST

Suite *reverse_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, reverse_usual);
    tcase_add_test(tcase_pos, reverse_one);

    suite_add_tcase(s, tcase_pos);

    return s;
}