#ifndef HEAD_H
#define HEAD_H

#define MISTAKE_STR_FIRST 1
#define MISTAKE_STR_SECOND 2
#define MISTAKE_SIZE 3
#define MISTAKE_STRLEN 10
#define OK 0

#define IS_SEP -4
#define IS_NOT_SEP 4
#define IS_UNIQUE 5
#define IS_NOT_UNIQUE -5
#define F_NO 0
#define F_YES 1
#define IS_OK_PRINT 1

#define MIN_LEN 2
#define MAX_LEN 257
#define MAX_LEN_WORD 16
#define LEN_SEP 8

int element_is_sep(char element);

int string_in_words(char *str, char (*array_word)[MAX_LEN_WORD]);

int is_element_in_array(const char *element, char (*array_word)[MAX_LEN_WORD], \
int size, int flag, int j);

int print_result(int is_ok);

int find_unique_word(char (*array_word_first)[MAX_LEN_WORD], \
char (*array_word_second)[MAX_LEN_WORD], int size_first, int size_second);

#endif