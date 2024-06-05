#include "check_decomposition.h"

void check_decomposition(node_t *head, int num)
{
    int rc;
    
    node_t *head_res = NULL;
    
    rc = number_decomposion(&head_res, num);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = comparison_of_lists(head, head_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    list_free(head);
    list_free(head_res);
}

START_TEST(decomposition_usual)
{
    int num = 145;
    
	node_t *node;
    node_t *head = NULL;
    node = node_create(5, 1);
    head = list_add_front(head, node);
    node = node_create(29, 1);
    head = list_add_front(head, node);

    check_decomposition(head, num);
}
END_TEST

START_TEST(decomposition_few_power)
{
    int num = 200;
    
	node_t *node;
    node_t *head = NULL;
    node = node_create(2, 3);
    head = list_add_front(head, node);
    node = node_create(5, 2);
    head = list_add_front(head, node);

    check_decomposition(head, num);
}
END_TEST

START_TEST(decomposition_many_divider)
{
    int num = 6006;
    
	node_t *node;
    node_t *head = NULL;
    node = node_create(2, 1);
    head = list_add_front(head, node);
    node = node_create(3, 1);
    head = list_add_front(head, node);
    node = node_create(7, 1);
    head = list_add_front(head, node);
    node = node_create(11, 1);
    head = list_add_front(head, node);
    node = node_create(13, 1);
    head = list_add_front(head, node);

    check_decomposition(head, num);
}
END_TEST

START_TEST(decomposition_impossible)
{
	int rc;
	
    int num = 1;
    
	node_t *head_res = NULL;
	
    rc = number_decomposion(&head_res, num);
    ck_assert_int_eq(rc, ERROR_DECOMPOSOTION);
}
END_TEST

Suite *decomposition_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, decomposition_usual);
    tcase_add_test(tcase_pos, decomposition_few_power);
    tcase_add_test(tcase_pos, decomposition_many_divider);

    suite_add_tcase(s, tcase_pos);
    
    TCase *tcase_neg;
    tcase_neg = tcase_create("negatives");
    tcase_add_test(tcase_neg, decomposition_impossible);
    
    suite_add_tcase(s, tcase_neg);

    return s;
}