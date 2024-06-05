#include "head.h"

int main(void)
{
    print_rules();

    short int rc;  
    
    float_number_t num_f = {.mantis_sign = '+', .mantissa = {'\0'}, \
    .eps_sign = '+', .eps_num = {'\0'}, .point_place = 0};

    if ((rc = read_float(&num_f) != OK))
        return rc;
    
    int_number_t num_i = {.sign = '+', .digit_part = {'\0'}};
    
    if ((rc = read_int(&num_i) != OK))
        return rc;
    
    int result[MANTISSA_MAX_LEN * 2] = {0}, res_power = 0, ind, end_ind = MANTISSA_MAX_LEN * 2 - 1;

    if ((rc = mul(num_f, num_i, result, &res_power, &ind, &end_ind)) != OK)
        return rc;
    
    print_result(num_f, num_i, result, res_power, ind, end_ind);
    
    return OK;  
}
