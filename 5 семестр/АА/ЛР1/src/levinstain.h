#ifndef DISTANCE_H
#define DISTANCE_H

#include <string.h>

#define MAX_STR_LEN 100

int find_distance(int action);

int lev(char *str_1, char *str_2, int print_table_flag);
int dameray_lev(char *str_1, char *str_2, int print_table_flag);
int dameray_lev_rec(char *str_1, char *str_2, int len_1, int len_2);
int dameray_lev_rec_hash(char *str_1, char *str_2);

#endif
