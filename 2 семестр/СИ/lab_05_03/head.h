#ifndef HEAD_H
#define HEAD_H

/* По заданию были выбраны:
целочисленный тип int
алгоритм сортировки пузырьком
сортировка по возрастанию*/

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MISTAKE_MAIN 1
#define MISTAKE_INPUT_MAIN -1

#define MISTAKE_OPENING_FILE -2
#define MEET_NOT_DIGIT -3
#define MISTAKE_FILE_SIZE -4
#define FILE_EMPTY -5

#define NUMBER_KEY 1
#define NUMBER_NAME_FILE 2
#define NUMBER_DIGIT_1 10
#define BASE 100
#define INPUT_SIZE 1

size_t get_file_size(FILE *f);
int key_is_not(char **argv);
void get_number_by_pos(FILE *f, const int pos, int *el);
void put_number_by_pos(FILE *f, const int pos, const int *el);
void sorting(FILE *f, const size_t);
int key_is_s(char **argv);

#endif
