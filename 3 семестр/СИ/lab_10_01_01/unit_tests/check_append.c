#include "check_append.h"

void check_append(node_t *head_a, node_t *head_b, node_t *head_res)
{
    int rc;
       
    append(&head_a, &head_b);

    rc = comparison_of_lists(head_a, head_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    free_list(head_a);
    free_list(head_res);
}

START_TEST(append_usual)
{   
    year_t array_a, array_b, array_res;
    node_t *head_a = NULL, *head_b = NULL, *head_res = NULL;

    array_a.array = malloc(4 * sizeof(int));
    array_a.size = 4;
    array_a.array[0] = 1984;
    array_a.array[1] = 1983;
    array_a.array[2] = 1988;
    array_a.array[3] = 2002;
    
    fill_list(&head_a, &array_a);
    
    array_b.array = malloc(5 * sizeof(int));
    array_b.size = 5;
    array_b.array[0] = 1765;
    array_b.array[1] = 1234;
    array_b.array[2] = 1900;
    array_b.array[3] = 1901;
    array_b.array[4] = 1902;
    
    fill_list(&head_b, &array_b);
    
    array_res.array = malloc(9 * sizeof(int));
    array_res.size = 9;
    array_res.array[0] = 1984;
    array_res.array[1] = 1983;
    array_res.array[2] = 1988;
    array_res.array[3] = 2002;
    array_res.array[4] = 1765;
    array_res.array[5] = 1234;
    array_res.array[6] = 1900;
    array_res.array[7] = 1901;
    array_res.array[8] = 1902;
    
    fill_list(&head_res, &array_res);

    check_append(head_a, head_b, head_res);
    
    free(array_a.array);
    free(array_b.array);
    free(array_res.array);
}
END_TEST

START_TEST(append_usual_second)
{   
    year_t array_a, array_b, array_res;
    node_t *head_a = NULL, *head_b = NULL, *head_res = NULL;

    array_a.array = malloc(3 * sizeof(int));
    array_a.size = 3;
    array_a.array[0] = 1234;
    array_a.array[1] = 1234;
    array_a.array[2] = 1234;
    
    fill_list(&head_a, &array_a);
    
    array_b.array = malloc(2 * sizeof(int));
    array_b.size = 2;
    array_b.array[0] = 1234;
    array_b.array[1] = 1234;
    
    fill_list(&head_b, &array_b);
    
    array_res.array = malloc(5 * sizeof(int));
    array_res.size = 9;
    array_res.array[0] = 1234;
    array_res.array[1] = 1234;
    array_res.array[2] = 1234;
    array_res.array[3] = 1234;
    array_res.array[4] = 1234;
    
    fill_list(&head_res, &array_res);

    check_append(head_a, head_b, head_res);
    
    free(array_a.array);
    free(array_b.array);
    free(array_res.array);
}
END_TEST

Suite *append_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, append_usual);
    tcase_add_test(tcase_pos, append_usual_second);

    suite_add_tcase(s, tcase_pos);

    return s;
}