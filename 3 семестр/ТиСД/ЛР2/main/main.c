#include <stdio.h>
#include <stdlib.h>

#include "table.h"

int main(void)
{
    setbuf(stdout, NULL);
    
    books_t books_arr[MAX_SIZE];
    keys_t keys_arr[MAX_SIZE];
    table_t table = {books_arr, keys_arr, 0};

    short int action_type, rc;

    while (1)
    {
        print_menu();

        if ((rc = read_action(&action_type)))
            return rc;

        if ((rc = do_action(action_type, &table)))
            return rc;
    }

    return EXIT_SUCCESS;
}
