#include "head.h"

int check_substr(const char *const name, const char *const substr)
{
    int len_name = strlen(name) - 1;
    int len_substr = strlen(substr) - 1;
    
    while (len_substr >= 0)
    {
        if (name[len_name] != substr[len_substr])
        {
            return NEGATIVE;
        }
        
        len_substr--;
        len_name--;
    }

    return OK;
}

int product_information(FILE *const f, const char *const substr)
{
    product_t product;
    int count = 0;
    const int size = get_file_size(f);

    for (int i = 1; i <= size; i++) 
    {
        if (get_value_by_pos(f, i, &product))
            return MISTAKE_READING;

        if (!check_substr(product.name, substr))
        {
            count++;
            printf("%s\n", product.name);
            printf("%s\n", product.manafacturer);
            printf("%u\n", product.price);
            printf("%u\n", product.count);
        }
    }

    if (0 == count)
        return NO_SUBSTR;

    return OK;
}

int key_is_fb(const int argc, char **argv)
{
    FILE *f;
    
    if (argc < MIN_ARGC + 1)
        return MISTAKE_ARGC;

    if ((f = fopen(argv[NUMBER_NAME_FILE], "rb")) == NULL)
        return MISTAKE_OPENING_FILE;

    if (!get_file_size(f))
    {
        fclose(f);
        return FILE_EMPTY;
    }
    
    if (product_information(f, argv[NUMBER_NAME_FILE + 1]))
    {
        fclose(f);
        return MISTAKE_INFO;
    }
    
    fclose(f);
    return OK; 
}
