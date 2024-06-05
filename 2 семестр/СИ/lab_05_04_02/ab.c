#include "head.h"

int find_pos(FILE *f, const product_t buf, const int size)
{
    product_t pr;
    int pos = 1;
    
    for (int i = 1; i <= size; i++)
    {
        if (get_value_by_pos(f, i, &pr))
            return MISTAKE_READING;

        if ((buf.price == pr.price && buf.count > pr.count) \
            || (buf.price > pr.price))
            break;

        pos++;
    }
    
    return pos;
}

int add_info(FILE *const f, const product_t buf)
{
    product_t pr;
    const int size = get_file_size(f);
    
    int pos = find_pos(f, buf, size);
    
    if (pos < 0)
        return MISTAKE_READING;
    
    for (int i = size; i >= pos; i--)
    {
        if (get_value_by_pos(f, i, &pr))
            return MISTAKE_READING;

        if (put_value_by_pos(f, (i + 1), pr))
            return MISTAKE_WRITING;
    }

    if (put_value_by_pos(f, pos, buf))
        return MISTAKE_WRITING;
    
   return OK;
}

int read_struct(FILE *const f)
{
    product_t buf_struct;
    memset(&buf_struct, 0, sizeof(product_t));

    if (scanf("%s", buf_struct.name) != INPUT_SIZE || \
        scanf("%s", buf_struct.manafacturer) != INPUT_SIZE || \
        scanf("%u", &buf_struct.price) != INPUT_SIZE || \
        scanf("%u", &buf_struct.count) != INPUT_SIZE)
        return NO_INPUT;

    if (add_info(f, buf_struct))
        return MISTAKE_INSERT;

    return OK;
}

int key_is_ab(const int argc, char **argv)
{
    FILE *f;
    
    if ((f = fopen(argv[NUMBER_NAME_FILE], "rb+")) == NULL)
        return MISTAKE_OPENING_FILE;
        
    if (!get_file_size(f))
    {
        fclose(f);
        return FILE_EMPTY;
    }

    if (read_struct(f))
    {
        fclose(f);
        return MISTAKE_INSERT;
    }

    fclose(f);
    return OK;
}
