#include "sort.h"

void swap(short int table, void *val1, void *val2)
{
    if (table)
    {
        books_t temp = *(books_t*)val1;
        *(books_t*)val1 = *(books_t*)(val2);
        *(books_t*)val2 = temp;
    }
    else
    {
        keys_t temp = *(keys_t*)val1;
        *(keys_t*)val1 = *(keys_t*)(val2);
        *(keys_t*)val2 = temp;
    }
}

int comparator_keys(const void *val1, const void *val2)
{
    return ((keys_t*)(val1))->size_book - ((keys_t*)(val2))->size_book;
}

int comparator_table(const void *val1, const void *val2)
{
    return ((books_t*)(val1))->size_book - ((books_t*)(val2))->size_book;
}

void bubble_sort(const int size, void *arr, int (*comparator)(const void *val1, const void *val2), 
short int table, size_t size_bytes)
{
    for (int i = 0; i < size * size_bytes - size_bytes; i += size_bytes)
    {
        for (int j = 0; j < size * size_bytes- i - size_bytes; j += size_bytes)
        {
            if ((*comparator)((arr + j), (arr + j + size_bytes)) > 0)
            {
                swap(table, (arr + j), (arr + j + size_bytes));
            } 
        }
    }
}
