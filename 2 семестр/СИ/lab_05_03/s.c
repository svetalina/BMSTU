#include "head.h"

void get_number_by_pos(FILE *f, const int pos, int *el)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    
    fread(el, sizeof(int), INPUT_SIZE, f);
}

void put_number_by_pos(FILE *f, const int pos, const int *el)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    
    fwrite(el, sizeof(int), INPUT_SIZE, f);
}

void sorting(FILE *f, const size_t file_size)
{
    int el_01, el_02;
    
    for (int i = 0 ; i < file_size / sizeof(int); i++) 
    { 
        for (int j = 0 ; j < file_size / sizeof(int); j++) 
        {  
            get_number_by_pos(f, i, &el_01); 
            get_number_by_pos(f, j, &el_02);
           
            if (el_01 < el_02)
            {           
                put_number_by_pos(f, i, &el_02);
                put_number_by_pos(f, j, &el_01);
            }
        }
    }
}

int key_is_s(char **argv)
{
    FILE *f;
    
    if ((f = fopen(argv[NUMBER_NAME_FILE], "rb+")) == NULL) 
        return MISTAKE_OPENING_FILE;
    
    size_t file_size = get_file_size(f);
    
    if (file_size == 0)
        return FILE_EMPTY;
    
    if (file_size % sizeof(int) > 0)
        return MISTAKE_FILE_SIZE;
    
    sorting(f, file_size);
    
    return OK;
}
