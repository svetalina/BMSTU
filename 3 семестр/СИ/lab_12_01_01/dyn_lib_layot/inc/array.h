#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_SYMBOL 3
#define ERROR_MEMORY 5
#define ERROR_FILTRATION_DATA 6
#define ERROR_EMPTY_FILTRATION 7

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL int ARR_DECL array_read(int **pb_array, int **pe_array, FILE *const f);
ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
ARR_DLL void ARR_DECL mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
ARR_DLL int ARR_DECL comparison_integers(const void *el_1, const void *el_2);

#endif
