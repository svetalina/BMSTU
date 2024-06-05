#include "check_sort.h" 

void check_sort(item_t **array_1, int size_1, item_t **array_true, int size_true)
{
    items_sort(array_1, size_1);

    int rc = comparison_of_array(array_1, size_1, array_true, size_true);
    
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    
    items_free_memory(array_1, size_1);
    items_free_memory(array_true, size_true);
}

START_TEST(sort_usual)
{
    item_t *array_1 = NULL;
    int size_1 = 5;
    items_change_memory(&array_1, size_1);
    
    (array_1 + 0)->name = strdup("qwe");
    (array_1 + 0)->mass = 54;
    (array_1 + 0)->volume = 12;
    
    (array_1 + 1)->name = strdup("rty");
    (array_1 + 1)->mass = 12;
    (array_1 + 1)->volume = 56;
    
    (array_1 + 2)->name = strdup("uio");
    (array_1 + 2)->mass = 7;
    (array_1 + 2)->volume = 1;
    
    (array_1 + 3)->name = strdup("asd");
    (array_1 + 3)->mass = 13;
    (array_1 + 3)->volume = 13;
    
    (array_1 + 4)->name = strdup("fgh");
    (array_1 + 4)->mass = 1235;
    (array_1 + 4)->volume = 5321;
    
    
    item_t *array_true = NULL;
    int size_true = 5;
    items_change_memory(&array_true, size_true);
    
    (array_true + 3)->name = strdup("qwe");
    (array_true + 3)->mass = 54;
    (array_true + 3)->volume = 12;
    
    (array_true + 0)->name = strdup("rty");
    (array_true + 0)->mass = 12;
    (array_true + 0)->volume = 56;
    
    (array_true + 4)->name = strdup("uio");
    (array_true + 4)->mass = 7;
    (array_true + 4)->volume = 1;
    
    (array_true + 2)->name = strdup("asd");
    (array_true + 2)->mass = 13;
    (array_true + 2)->volume = 13;
    
    (array_true + 1)->name = strdup("fgh");
    (array_true + 1)->mass = 1235;
    (array_true + 1)->volume = 5321;

    check_sort(&array_1, size_1, &array_true, size_true);
}
END_TEST

START_TEST(sort_one_el)
{
    item_t *array_1 = NULL;
    int size_1 = 1;
    items_change_memory(&array_1, size_1);
    
    (array_1 + 0)->name = strdup("vbnh");
    (array_1 + 0)->mass = 21;
    (array_1 + 0)->volume = 7;
    
    
    item_t *array_true = NULL;
    int size_true = 1;
    items_change_memory(&array_true, size_true);
    
    (array_true + 0)->name = strdup("vbnh");
    (array_true + 0)->mass = 21;
    (array_true + 0)->volume = 7;

    check_sort(&array_1, size_1, &array_true, size_true);
}
END_TEST

Suite *sort_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, sort_usual);
    tcase_add_test(tcase_pos, sort_one_el);

    suite_add_tcase(s, tcase_pos);

    return s;
}