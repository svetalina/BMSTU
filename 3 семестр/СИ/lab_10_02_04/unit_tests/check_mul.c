#include "check_mul.h"

void check_mul(node_t *head_a, node_t *head_b, node_t *head_res)
{
    int rc;
    
    node_t *head_func = NULL;
    
    list_mul(head_a, head_b, &head_func);

    rc = comparison_of_lists(head_func, head_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    list_free(head_a);
	list_free(head_b);
	list_free(head_res);
    list_free(head_func);
}

START_TEST(mul_different_divider)
{ 
	node_t *node;
	
    node_t *head_a = NULL;
    node = node_create(5, 1);
    head_a = list_add_front(head_a, node);
    node = node_create(29, 1);
    head_a = list_add_front(head_a, node);
	
	node_t *head_b = NULL;
    node = node_create(3, 2);
    head_b = list_add_front(head_b, node);
    node = node_create(11, 1);
    head_b = list_add_front(head_b, node);
	
	node_t *head_res = NULL;
    node = node_create(3, 2);
    head_res = list_add_front(head_res, node);
	node = node_create(5, 1);
    head_res = list_add_front(head_res, node);
    node = node_create(11, 1);
    head_res = list_add_front(head_res, node);
	node = node_create(29, 1);
    head_res = list_add_front(head_res, node);

    check_mul(head_a, head_b, head_res);
}
END_TEST

START_TEST(mul_equal_divider)
{ 
	node_t *node;
	
    node_t *head_a = NULL;
    node = node_create(5, 2);
    head_a = list_add_front(head_a, node);
    node = node_create(7, 3);
    head_a = list_add_front(head_a, node);
	
	node_t *head_b = NULL;
    node = node_create(3, 2);
    head_b = list_add_front(head_b, node);
    node = node_create(5, 4);
    head_b = list_add_front(head_b, node);
	node = node_create(7, 1);
    head_b = list_add_front(head_b, node);
	
	node_t *head_res = NULL;
    node = node_create(3, 2);
    head_res = list_add_front(head_res, node);
	node = node_create(5, 6);
    head_res = list_add_front(head_res, node);
    node = node_create(7, 4);
    head_res = list_add_front(head_res, node);

    check_mul(head_a, head_b, head_res);
}
END_TEST

Suite *mul_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, mul_different_divider);
    tcase_add_test(tcase_pos, mul_equal_divider);

    suite_add_tcase(s, tcase_pos);
    return s;
}