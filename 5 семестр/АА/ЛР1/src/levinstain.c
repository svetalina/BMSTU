#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <limits.h>

#include "levinstain.h"
#include "matrix.h"
#include "error.h"

int min(int n, ...)
{
	int el, res = INT_MAX;
    va_list factor;         
    va_start(factor, n);
    for(int i = 0; i < n; i++)
    {
		el = va_arg(factor, int);
        if (el < res)
			res = el;
    }
    va_end(factor); 
    return res;
}

int lev(char *str_1, char *str_2, int print_table_flag)
{
    matrix_t *m = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);

    m->elements[0][0] = 0;
    for (size_t i = 1; i < m->rows; ++i)
        m->elements[i][0] = i;
    for (size_t i = 1; i < m->cols; ++i)
        m->elements[0][i] = i;

    for (size_t i = 1; i < m->rows; ++i)
        for (size_t j = 1; j < m->cols; ++j) 
		{
            int offset = str_1[i - 1] == str_2[j - 1] ? 0 : 1;
            m->elements[i][j] = min(3, m->elements[i][j - 1] + 1,
                                       m->elements[i - 1][j] + 1,
                                       m->elements[i - 1][j - 1] + offset);
        }

    if (print_table_flag) {
        printf("Таблица расстояний Ливенштейна:\n");
        print_matrix(m);
    }

    int res = m->elements[m->rows - 1][m->cols - 1];
    free_matrix(m);

    return res;
}

int dameray_lev(char *str_1, char *str_2, int print_table_flag)
{
    matrix_t *m = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);

    m->elements[0][0] = 0;
    for (size_t i = 1; i < m->rows; ++i)
        m->elements[i][0] = i;
    for (size_t i = 1; i < m->cols; ++i)
        m->elements[0][i] = i;

    for (size_t i = 1; i < m->rows; ++i)
        for (size_t j = 1; j < m->cols; ++j) {
            int offset = str_1[i - 1] == str_2[j - 1] ? 0 : 1;
            m->elements[i][j] = min(3, m->elements[i][j - 1] + 1,
                                       m->elements[i - 1][j] + 1,
                                       m->elements[i - 1][j - 1] + offset);
            if (j > 1 && i > 1 && str_1[i - 1] == str_2[j - 2] && str_1[i - 2] == str_2[j - 1])
                m->elements[i][j] = min(2, m->elements[i][j], m->elements[i - 2][j - 2] + 1);
        }

    if (print_table_flag) {
        printf("Таблица расстояний Дамерау-Ливенштейна:\n");
        print_matrix(m);
    }

    int res = m->elements[m->rows - 1][m->cols - 1];
    free_matrix(m);

    return res;
}

int dameray_lev_rec(char *str_1, char *str_2, int len_1, int len_2)
{
    if (len_1 == 0)
        return len_2;
    if (len_2 == 0)
        return len_1;

    int offset = str_1[len_1 - 1] == str_2[len_2 - 1] ? 0 : 1;
    int res = min(3, dameray_lev_rec(str_1, str_2, len_1 - 1, len_2) + 1,
                     dameray_lev_rec(str_1, str_2, len_1, len_2 - 1) + 1,
                     dameray_lev_rec(str_1, str_2, len_1 - 1, len_2 - 1) + offset);
    if (len_1 > 1 && len_2 > 1 && str_1[len_1 - 1] == str_2[len_2 - 2] && str_1[len_1 - 2] == str_2[len_2 - 1])
        res = min(2, res, dameray_lev_rec(str_1, str_2, len_1 - 2, len_2 - 2) + 1);

    return res;
}

int dameray_lev_rec_hash_call(char *str_1, char *str_2, int len_1, int len_2, matrix_t *mat)
{
    if (len_1 == 0)
        return (mat->elements)[len_1][len_2] = len_2;
    if (len_2 == 0)
        return (mat->elements)[len_1][len_2] = len_1;

    if (mat->elements[len_1 - 1][len_2] == -1)
        dameray_lev_rec_hash_call(str_1, str_2, len_1 - 1, len_2, mat);
    if (mat->elements[len_1][len_2 - 1] == -1)
        dameray_lev_rec_hash_call(str_1, str_2, len_1, len_2 - 1, mat);
    if (mat->elements[len_1 - 1][len_2 - 1] == -1)
        dameray_lev_rec_hash_call(str_1, str_2, len_1 - 1, len_2 - 1, mat);

    int offset = str_1[len_1 - 1] == str_2[len_2 - 1] ? 0 : 1;
    mat->elements[len_1][len_2] = min(3, mat->elements[len_1][len_2 - 1] + 1,
										 mat->elements[len_1 - 1][len_2] + 1,
                                         mat->elements[len_1 - 1][len_2 - 1] + offset);
    if (len_1 > 1 && len_2 > 1 && str_1[len_1 - 1] == str_2[len_2 - 2] && str_1[len_1 - 2] == str_2[len_2 - 1]) {
        if (mat->elements[len_1 - 2][len_2 - 2] == -1)
            dameray_lev_rec_hash_call(str_1, str_2, len_1 - 2, len_2 - 2, mat);
        mat->elements[len_1][len_2] = min(2, mat->elements[len_1][len_2], mat->elements[len_1 - 2][len_2 - 2] + 1);
    }

    return mat->elements[len_1][len_2];
}

int dameray_lev_rec_hash(char *str_1, char *str_2)
{
    matrix_t *m = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);
    clear_matrix(m);

    int res = dameray_lev_rec_hash_call(str_1, str_2, strlen(str_1), strlen(str_2), m);
    free_matrix(m);

    return res;
}


int read_words(char *word_1, char *word_2)
{
	puts("Введите два слова(концом ввода слова считается enter):");
    if (scanf("%s", word_1) != 1 || word_1[MAX_STR_LEN] != '\0')
        return ERROR_WORD_1;
    if (scanf("%s", word_2) != 1 || word_2[MAX_STR_LEN] != '\0')
        return ERROR_WORD_2;

    return EXIT_SUCCESS;
}

int find_distance(int action)
{
	int rc;
	
	char word_1[MAX_STR_LEN + 1] = {'\0'};
	char word_2[MAX_STR_LEN + 1] = {'\0'};
	if (rc = read_words(word_1, word_2))
		return rc;
	
	int dist = 0;
	switch (action) {
		case 1:
			dist = lev(word_1, word_2, 1);
			break;
		case 2:
			dist = dameray_lev(word_1, word_2, 1);
			break;
		case 3:
			dist = dameray_lev_rec(word_1, word_2, strlen(word_1), strlen(word_2));
		    break;
		case 4:
			dist = dameray_lev_rec_hash(word_1, word_2);
			break;
		default:
			dist = -1;
			break;
	}
			
	printf("Найденное расстояние между %s и %s = %d\n\n", word_1, word_2, dist);
		
	return EXIT_SUCCESS;
}
