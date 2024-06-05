#include "check_sqr.h"

void check_sqr(node_t *head)
{
    int rc;
    
    node_t *head_res = NULL;
    
    list_sqr(&head_res);

    rc = comparison_of_lists(head, head_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    list_free(head);
    list_free(head_res);
}

START_TEST(sqr_usual)
{ 
	node_t *node;
    node_t *head = NULL;
    node = node_create(5, 2);
    head = list_add_front(head, node);
    node = node_create(29, 2);
    head = list_add_front(head, node);

    check_sqr(head);
}
END_TEST

START_TEST(sqr_few_power)
{
	node_t *node;
    node_t *head = NULL;
    node = node_create(2, 6);
    head = list_add_front(head, node);
    node = node_create(5, 4);
    head = list_add_front(head, node);

    check_sqr(head);
}
END_TEST

START_TEST(sqr_many_divider)
{
	node_t *node;
    node_t *head = NULL;
    node = node_create(2, 2);
    head = list_add_front(head, node);
    node = node_create(3, 2);
    head = list_add_front(head, node);
    node = node_create(7, 2);
    head = list_add_front(head, node);
    node = node_create(11, 2);
    head = list_add_front(head, node);
    node = node_create(13, 2);
    head = list_add_front(head, node);

    check_sqr(head);
}
END_TEST

Suite *sqr_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, sqr_usual);
    tcase_add_test(tcase_pos, sqr_few_power);
    tcase_add_test(tcase_pos, sqr_many_divider);

    suite_add_tcase(s, tcase_pos);
    return s;
}