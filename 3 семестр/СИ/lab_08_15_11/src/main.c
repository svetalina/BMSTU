#include <string.h>
#include "matrix.h"
#include "file.h"

int main(int argc, char **argv)
{   
    int rc;
    
    if ((argc != 5 && argc != 4) || (argc == 4 && strcmp(argv[1], "o") != 0))
        return ERROR_INPUT_MAIN;
    
    matrix_t mtr_1 = { NULL, 0, 0 };
    if ((rc = matrix_filling(argv[2], &mtr_1)))
        return rc;
    
    int key_is_a = strcmp(argv[1], "a");
    int key_is_m = strcmp(argv[1], "m");
    if (key_is_a == 0 || key_is_m == 0)
    {       
        matrix_t mtr_2 = { NULL, 0, 0 };
        if ((rc = matrix_filling(argv[3], &mtr_2)))
        {
            free(mtr_1.mtr);
            return rc;
        }
        
        matrix_t res = { NULL, 0, 0 };
        if ((rc = res_matrix_create(&mtr_1, &mtr_2, &res, key_is_a)))
            return rc;
        
        if (key_is_a == 0)
            matrix_addition(&mtr_1, &mtr_2, &res);
        if (key_is_m == 0)
            matrix_multiplication(&mtr_1, &mtr_2, &res); 
        free(mtr_1.mtr);
        free(mtr_2.mtr);
        
        if ((rc = matrix_print_main(argv[4], &res)))
            return rc; 

        return EXIT_SUCCESS;        
    }
    
    if (strcmp(argv[1], "o") == 0)
    {     
        matrix_t res = { NULL, 0, 0 };
        if ((rc = identity_matrix_create(&mtr_1, &res)))
            return rc;
      
        if ((rc = matrix_inversion(&mtr_1, &res)))
            return rc;
        free(mtr_1.mtr);
        
        if ((rc = matrix_print_main(argv[3], &res)))
            return rc;
        
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;  
}
