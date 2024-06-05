#include "check_div.h"

void check_div(node_t *head_a, node_t *head_b, int res)
{
    ck_assert_int_eq(list_delete_equal_num(head_a, head_b), res);
    
    list_free(head_a);
	list_free(head_b);
}

START_TEST(div_different_divider)
{ 
	node_t *node;
	
    node_t *head_a = NULL;
    node = node_create(5, 2);
    head_a = list_add_front(head_a, node);
    node = node_create(29, 1);
    head_a = list_add_front(head_a, node);
	
	node_t *head_b = NULL;
    node = node_create(3, 2);
    head_b = list_add_front(head_b, node);
    node = node_create(11, 1);
    head_b = list_add_front(head_b, node);
	
	int res = 7;

    check_div(head_a, head_b, res);
}
END_TEST

START_TEST(div_equal_divider)
{ 
	node_t *node;
	
    node_t *head_a = NULL;
	node = node_create(3, 2);
    head_a = list_add_front(head_a, node);
    node = node_create(5, 2);
    head_a = list_add_front(head_a, node);
	node = node_create(7, 1);
    head_a = list_add_front(head_a, node);
	
	node_t *head_b = NULL;
    node = node_create(3, 1);
    head_b = list_add_front(head_b, node);
    node = node_create(5, 3);
    head_b = list_add_front(head_b, node);
	
	int res = 4;

    check_div(head_a, head_b, res);
}
END_TEST

Suite *div_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, div_different_divider);
    tcase_add_test(tcase_pos, div_equal_divider);

    suite_add_tcase(s, tcase_pos);
    return s;
}