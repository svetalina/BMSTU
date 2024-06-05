#include "file.h"
#include "array.h"
#include "element.h"

#define ERROR_INPUT_MAIN 1

int main(int argc, const char **argv)
{
    if ((argc != 4 && argc != 3) || (argc == 4 && *argv[3] != 'f'))
        return ERROR_INPUT_MAIN;
    
    int rc, counter_num;
    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL)
        return ERROR_FILE_OPEN;
    if ((rc = file_count_numbers(&counter_num, f)))
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
    if ((rc = array_read(&pb_array, &pe_array, f)))
    {
        fclose(f);
        return rc;
    }
    
    if (argc == 4)
    {
        int *pbf_array = NULL, *pef_array = NULL;
        rc = key(pb_array, pe_array, &pbf_array, &pef_array);
        if (rc)
        {
            free(pb_array);
            free(pbf_array);
            fclose(f);
            return rc;
        }
        free(pb_array);
        pb_array = pbf_array;
        pe_array = pef_array;
    }
    
    mysort(pb_array, pe_array - pb_array, sizeof(int), comparison_integers);
    
    if ((f = fopen(argv[2], "w")) == NULL)
        return ERROR_FILE_OPEN;
    rc = file_write(pb_array, pe_array, f);
    
    free(pb_array);
    return rc;
}