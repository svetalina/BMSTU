#include "head.h"

int copy_file(FILE *const f_in, FILE *const f_out)
{
    product_t product;
    int size = get_file_size(f_in);

    for (int i = 1; i <= size; i++)
    {
        if (get_value_by_pos(f_in, i, &product))
            return MISTAKE_READING;
            
        if (put_value_by_pos(f_out, i, product))
            return MISTAKE_WRITING;
    }
    
    return OK;
}

int sort_file(FILE *const f)
{
    product_t pr1, pr2, buf;
    const int size = get_file_size(f);

    for (int i = 1; i < size; i++)
    {
        int min_ind = i;
        
        for (int j = i + 1; j <= size; j++)
        {
            if (get_value_by_pos(f, j, &pr1) || get_value_by_pos(f, min_ind, &pr2))
                return MISTAKE_READING;

            min_ind = (pr1.price > pr2.price) ? j : min_ind;
            min_ind = (pr1.price == pr2.price && pr1.count > pr2.count) ? j : min_ind;
        }
        
        if (get_value_by_pos(f, i, &buf) || get_value_by_pos(f, min_ind, &pr1))
            return MISTAKE_READING;

        if (put_value_by_pos(f, i, pr1) || put_value_by_pos(f, min_ind, buf))
            return MISTAKE_WRITING;
    }

    return OK;
}

int key_is_sb(const int argc, char **argv)
{
    FILE *f_in, *f_out;
    
    if (argc < MIN_ARGC + 1)
        return MISTAKE_ARGC;

    if ((f_in = fopen(argv[NUMBER_NAME_FILE], "rb")) == NULL || 
        (f_out = fopen(argv[NUMBER_NAME_FILE + 1], "rb+")) == NULL)
        return MISTAKE_OPENING_FILE;
    
    if (!get_file_size(f_in))
        return FILE_EMPTY;

    if (copy_file(f_in, f_out))
    {
        is_fclose(f_in, f_out);
        return MISTAKE_COPY;
    }
    
    if (sort_file(f_out))
    {
        is_fclose(f_in, f_out);
        return MISTAKE_SORT;
    }

    is_fclose(f_in, f_out);
    return OK;
}
