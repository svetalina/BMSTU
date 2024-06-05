#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define OK 0
#define MISTAKE_ARGC 1
#define MISTAKE_OPENING_FILE 2
#define FILE_EMPTY 3
#define MISTAKE_READING 4
#define MISTAKE_WRITING 5
#define ERROR 53

#define MISTAKE_COPY 6
#define MISTAKE_SORT 7

#define MISTAKE_INFO 8
#define NO_SUBSTR 9

#define NO_INPUT 10
#define MISTAKE_INSERT 11

#define NEGATIVE 1

#define NAME_SIZE 31
#define MANUF_SIZE 16
#define NUMBER_KEY 1
#define MIN_ARGC 3
#define NUMBER_NAME_FILE 2
#define INPUT_SIZE 1
#define OUTPUT_SIZE 1

typedef struct
{
    char name[NAME_SIZE];
    char manafacturer[MANUF_SIZE];
    uint32_t price;
    uint32_t count;
} product_t;

int copy_file(FILE *const f_in, FILE *const f_out);
int sort_file(FILE *const f);
int key_is_sb(const int argc, char **argv);
int check_substr(const char *const name, const char *const substr);
int product_information(FILE *const f, const char *const substr);
int product_information(FILE *const f, const char *const substr);
int key_is_fb(const int argc, char **argv);
int add_info(FILE *const f, const product_t buf);
int read_struct(FILE *const f);
int key_is_ab(const int argc, char **argv);
size_t get_file_size(FILE *f);
void is_fclose(FILE *f_in, FILE *f_out);
int get_value_by_pos(FILE *const f, const int pos, product_t *const el);
int put_value_by_pos(FILE *const f, const int pos, const product_t el);

#endif