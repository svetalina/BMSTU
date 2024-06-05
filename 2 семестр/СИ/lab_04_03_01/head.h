#ifndef HEAD_H
#define HEAD_H

#define MISTAKE_STR 1
#define FEW_WORDS -2
#define MISTAKE_NEW_STR 5
#define EMPTY_NEW_STRING -3
#define GOOD_NEW_STRING 4
#define OK 0

#define NO_FIRST_LETTER 0
#define YES_FIRST_LETTER 1
#define TOO_LONG_WORD -5

#define MAX_LEN 257
#define MAX_LEN_WORD 18
#define LEN_SEP 15

int string_in_words(char *str, char **array);
int is_first_letter(const char *word, const int position);
void creat_new_str(char *new_str, const char *word);
int call_all_funcs_str(char *str);
void print_result(char *new_str);
void print_result(char *new_str);

#endif
