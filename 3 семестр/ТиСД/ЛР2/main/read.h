#ifndef __READ_H__
#define __READ_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"

#define MIN_MENU 0
#define MAX_MENU 10

#define MIN_SIZE_BOEXIT_SUCCESS 1
#define MAX_SIZE_BOEXIT_SUCCESS 100000

#define MAX_SIZE 1000

#define ERROR_INPUT -1
#define ERROR_MENU_NUMBER -2
#define ERROR_FILE_SIZE -3
#define ERROR_SYMBOLS -5
#define ERROR_SIZE_BOOK -6


short int read_action(short *action_type);
short read_file_size(table_t *table, FILE *f);
short read_books_author(table_t *table, FILE *f, short int i);
short int read_books_name(table_t *table, FILE *f, short int i);
short int read_books_publish_house(table_t *table, FILE *f, short int i);
short int read_books_is_type(table_t *table, FILE *f, short int i);
short int read_technical(table_t *table, FILE *f, short int i);
short int read_fiction(table_t *table, FILE *f, short int i);
short int read_children(table_t *table, FILE *f, short int i);
short read_pos_to_del(table_t *const table, int *pos);
short read_branch(char *brach_str);
short reade_year(int *year_str);

#endif
