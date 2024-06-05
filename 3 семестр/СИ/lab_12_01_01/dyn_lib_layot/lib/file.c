#include "file.h"

FILE_DLL int FILE_DECL  file_count_numbers(int *const counter_num, FILE *const f)
{
    int num;
    *counter_num = 0;
	
    while (fscanf(f, "%d", &num) == 1)
        (*counter_num)++;
    
    if (!feof(f))
        return ERROR_SYMBOL;
    if (*counter_num == 0)
        return ERROR_EMPTY_FILE;
    
    return EXIT_SUCCESS;
}

FILE_DLL int FILE_DECL file_write(int *pb_array, int *pe_array, FILE *f)
{
    const int *begin = pb_array;
    
    while (begin < pe_array)
        fprintf(f, "%d ", *(begin++));
    
    fclose(f);
    return EXIT_SUCCESS;
}
