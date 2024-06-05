#ifndef HEAD_H

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <regex.h>

#define OK 0
#define READ_ERROR -1
#define PATTERN_ERROR -2
#define ERR_POWER_OVERFLOW -5
#define EMPTY_ERROR -6

#define READ_OK 1
#define MANTISSA_MAX_LEN 30
#define EPS_MAX_LEN 5
#define SIZE_STRING_FLOAT 40
#define SIZE_STRING_INT 32

#define r "\x1b[31m"
#define y "\x1b[33m"
#define g "\x1b[32m"
#define w "\x1b[0m"

#define PATTERN "^[+-]{0,1}[0123456789.]{1,31}[eE]{0,1}[+-]{0,1}[0-9]{0,5}$"

typedef struct
{
    char mantis_sign;
    char mantissa[MANTISSA_MAX_LEN];
    char eps_sign;
    char eps_num[EPS_MAX_LEN];
    int point_place;
} float_number_t;

typedef struct
{
    char sign;
    char digit_part[MANTISSA_MAX_LEN];
} int_number_t;


void look_for_mistake_float(char *num);
void do_struct(float_number_t *number, char *num);
short int read_float(float_number_t *number);
short int read_int(int_number_t *number);
void print_rules(void);
short int mul(float_number_t num1, int_number_t num2, int *result, int *res_power, int *ind, int *end_ind);
void print_result(float_number_t num1, int_number_t num2, int *result, int res_power, int ind, int end_ind);

#endif
