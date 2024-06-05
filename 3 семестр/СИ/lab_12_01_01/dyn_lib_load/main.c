#include <windows.h>
#include "file.h"
#include "array.h"

typedef int (__cdecl *fn_file_count_numbers_t)(int *const, FILE *const);
typedef int (__cdecl *fn_file_write_t)(int *, int *, FILE *);

typedef int (__cdecl *fn_comparison_integers_t)(const void *, const void *);
typedef int (__cdecl *fn_array_read_t)(int **, int **, FILE *const);
typedef int (__cdecl *fn_key_t)(const int *, const int *, int **, int **);
typedef void (__cdecl *fn_mysort_t)(void *, size_t, size_t, int (*)(const void *, const void *));
typedef void (__cdecl *fn_print_t)(const int*, int);

#define ERROR_INPUT_MAIN 1
#define ERROR_LIB 8
#define ERROR_FUNC 9

int main(int argc, const char **argv)
{
    if ((argc != 4 && argc != 3) || (argc == 4 && *argv[3] != 'f'))
	{
        return ERROR_INPUT_MAIN;
	}
	
	HMODULE file_lib, arr_lib;
    if (!(file_lib = LoadLibrary("libfile.dll")) \
	|| !(arr_lib = LoadLibrary("libarray.dll")))
		return ERROR_LIB;
	
	fn_file_count_numbers_t pcount_num;
	fn_file_write_t pwrite;
    fn_comparison_integers_t pcompare_int;
	fn_array_read_t pread;
	fn_key_t pkey;
	fn_mysort_t pmysort;
    if (!(pcount_num = (fn_file_count_numbers_t) GetProcAddress(file_lib, "file_count_numbers")) \
	|| !(pwrite = (fn_file_write_t) GetProcAddress(file_lib, "file_write")) \
	|| !(pcompare_int = (fn_comparison_integers_t) GetProcAddress(arr_lib, "comparison_integers")) \
	|| !(pread = (fn_array_read_t) GetProcAddress(arr_lib, "array_read")) \
	|| !(pkey = (fn_key_t) GetProcAddress(arr_lib, "key")) \
	|| !(pmysort = (fn_mysort_t) GetProcAddress(arr_lib, "mysort")))
    {
		FreeLibrary(file_lib);
		FreeLibrary(arr_lib);
		return ERROR_FUNC;
    }
    
    int rc, counter_num;
    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL)
        return ERROR_FILE_OPEN;
    if ((rc = pcount_num(&counter_num, f)))
    {
        fclose(f);
        return rc;
    }
    fseek(f, 0, SEEK_SET);
    
    int *pb_array;
    if ((pb_array = malloc(counter_num * sizeof(int))) == NULL)
    {
        fclose(f);
        return ERROR_MEMORY;
    }
    int *pe_array = pb_array + counter_num;
    if ((rc = pread(&pb_array, &pe_array, f)))
    {
        fclose(f);
		goto free_lib;
    }
    
    if (argc == 4)
    {
        int *pbf_array = NULL, *pef_array = NULL;
        if ((pbf_array = malloc((pe_array - pb_array) * sizeof(int))) == NULL)
            rc = ERROR_MEMORY;
    
        rc = pkey(pb_array, pe_array, &pbf_array, &pef_array);
        if (rc)
        {
            free(pb_array);
            free(pbf_array);
            fclose(f);
            goto free_lib;
        }
        free(pb_array);
        pb_array = pbf_array;
        pe_array = pef_array;
    }
    
    pmysort(pb_array, pe_array - pb_array, sizeof(int), pcompare_int);
    
    if ((f = fopen(argv[2], "w")) == NULL)
	{
		goto free_lib;
        rc = ERROR_FILE_OPEN;
	}
    rc = pwrite(pb_array, pe_array, f);
    
    free(pb_array);
	
	free_lib:
		FreeLibrary(file_lib);
		FreeLibrary(arr_lib);
	return rc;
}
