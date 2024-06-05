#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"

#define GHZ 1500000000

void print_rules();
void print_menu();
void print_table_keys(const table_t table);
void print_table(const table_t table, short int keys);
void print_sorts_vs_results(int64_t total_ticks, short sort_type, short table_type);
void print_by_condition(const table_t table, int i);

#endif
