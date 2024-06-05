#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef FUNC_EXPORTS
#define FUNC_DLL __declspec(dllexport)
#else
#define FUNC_DLL __declspec(dllimport)
#endif

#define FUNC_DECL __cdecl

FUNC_DLL void FUNC_DECL fill_array(int *array, int size);
FUNC_DLL int FUNC_DECL fill_array_after_even(int *arr, int size, int *arr_res, int size_res, int num);

#endif
