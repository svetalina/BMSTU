#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN 2
#define ERROR_SYMBOL 3
#define ERROR_EMPTY_FILE 4

#ifdef FILE_EXPORTS
#define FILE_DLL __declspec(dllexport)
#else
#define FILE_DLL __declspec(dllimport)
#endif

#define FILE_DECL __cdecl

FILE_DLL int FILE_DECL file_count_numbers(int *const counter_num, FILE *const f);
FILE_DLL int FILE_DECL file_write(int *pb_array, int *pe_array, FILE *f);

#endif

