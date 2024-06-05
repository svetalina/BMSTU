#include "head.h"

size_t get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    
    return file_size;
}

int key_is_not(char **argv)
{
    FILE *f;
    
    if ((f = fopen(argv[3], "wb")) == NULL)
        return MISTAKE_OPENING_FILE;
    
    for (int i = 0; i < NUMBER_DIGIT_1; i++)
    {
        int num = rand() % BASE;
        fwrite(&num, sizeof(int), INPUT_SIZE, f);
    }
    
    fclose(f);
    return OK;
}

int key_is_p(char **argv)
{
    FILE *f;
    
    if ((f = fopen(argv[NUMBER_NAME_FILE], "rb")) == NULL) 
        return MISTAKE_OPENING_FILE;
    
    size_t file_size = get_file_size(f);
    
    if (file_size == 0)
        return FILE_EMPTY;
    
    if (file_size % sizeof(int) > 0)
        return MISTAKE_FILE_SIZE;

    int num;
    
    fseek(f, 0, SEEK_SET);
    
    while (0 != fread(&num, sizeof(int), INPUT_SIZE, f))
        printf("%d ", num);

    return feof(f) ? OK : MEET_NOT_DIGIT;
}

int main(int argc, char **argv)
{        
    if (argc == 4)
        return key_is_not(argv);
    
    if (*argv[NUMBER_KEY] == 'p')
        return key_is_p(argv);
        
    if (*argv[NUMBER_KEY] == 's')
        return key_is_s(argv);
        
    return MISTAKE_MAIN;
}
