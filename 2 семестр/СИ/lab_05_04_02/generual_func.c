#include "head.h"

size_t get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f) / sizeof(product_t);
    fseek(f, 0, SEEK_SET);
    
    return file_size;
}

void is_fclose(FILE *f_in, FILE *f_out)
{
    fclose(f_in);
    fclose(f_out);
}

int get_value_by_pos(FILE *const f, const int pos, product_t *const el)
{
    fseek(f, pos * sizeof((*el)) - sizeof((*el)), SEEK_SET);
    
    if (fread(el, sizeof((*el)), INPUT_SIZE, f) != INPUT_SIZE)
        return MISTAKE_READING;
        
    return OK;
}

int put_value_by_pos(FILE *const f, const int pos, const product_t el)
{
    fseek(f, pos * sizeof(el) - sizeof(el), SEEK_SET);
    
    if (fwrite(&el, sizeof(el), OUTPUT_SIZE, f) != OUTPUT_SIZE)
        return MISTAKE_WRITING;
    
    return OK;
}
