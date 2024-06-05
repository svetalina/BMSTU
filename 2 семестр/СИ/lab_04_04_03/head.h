#ifndef HEAD_H
#define HEAD_H

#define WRONG_LEN 10
#define YES_DIGIT 1
#define NOT_DIGIT 0
#define NOT_CODE_COUNTRY -1
#define YES_CODE_OPERATOR 1
#define NOT_CODE_OPERATOR 0
#define YES_D 1
#define NOT_D 0
#define YES_NUMBER 1
#define NOT_NUMBER 0
#define YES_SEP 0
#define NOT_SEP 1
#define OK 0

#define SIZE_STR 260
#define MAX_LEN 256
#define LEN_SEP 7
#define CODE_OPERATORA 3
#define COUNT_D_ONE 3
#define COUNT_D_TWO 2
#define NUMBER_OF_PARTS 2
#define NUMBER_OF_HYPHENS 3

int check_digit(const int digit);
int check_code_operator(const char *str, const int position_start);
int check_code_country(const char *str, const int position_start);
int check_part_with_d(const char *str, const int position_start);
int is_sep(const char element);

#endif
