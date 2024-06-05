#ifndef CHECK_SORT_H
#define CHECK_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
void element_swap(char *one_el, char *two_el, size_t size);
int comparison_integers(const void *el_1, const void *el_2);

int comparison_of_arrays(int *array_one, int *array_two, int len);
void check_sort(int *array_one, const int len_one, int *array_two, const int len_two);
Suite *sort_suite(Suite *s);

#endif