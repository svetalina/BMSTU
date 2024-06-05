#ifndef __TABLE_OPERATIONS_H__
#define __TABLE_OPERATIONS_H__

#include <stdio.h>
#include <stddef.h>
#include "structures.h"
#include "time.h"
#include "sort.h"
#include "read.h"
#include "print.h"

#define FILE_NAME "data.txt"

#define ERROR_OPEN_FILE -7
#define TABLE_IS_FULL -8
#define TABLE_IS_EMPTY -9
#define NO_MATCHES -10
#define NO_BOOK -11

void clear_table(table_t *const table);
short load_data(table_t *const table, FILE *f, short start, short end);
void update_keys(table_t *const table, const short i, const short id, const short size_book);
short upload_from_file(table_t *const table);
short load_data_one(table_t *const table, FILE *f, short start, short end);
short add_to_end(table_t *const table);
short check_size(short size);
void del_by_pos(table_t *const table, int del_ind_keys, int del_ind_table);
short del_by_pos_main(table_t *const table);
short qs_vs_bubble(table_t *const table);
short find_books(table_t *const table, char *const branch_str, const int year_str);
short find_book_by_condition(table_t *const table);
short int do_action(short int action_type, table_t *table);

#endif
