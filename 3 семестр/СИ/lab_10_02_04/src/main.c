#include "list.h"
#include "node.h"
#include "number.h"

#include <string.h>

#define ERROR_READ_ACTION_TYPE 1
#define ERROR_VALUE_ACTION_TYPE 5

#define OUT 1
#define SQR 2
#define MUL 3
#define DIV 4

int check_action_type(char *action_type)
{
    if (strcmp(action_type, "out") == 0)
        return OUT;
    if (strcmp(action_type, "sqr") == 0)
        return SQR;
    if (strcmp(action_type, "mul") == 0)
        return MUL;
    if (strcmp(action_type, "div") == 0)
        return DIV;
    return ERROR_VALUE_ACTION_TYPE;
}

int main(void)
{ 
    int rc;
    
    char action_type[4];
    if (scanf("%s", action_type) != 1)
        return ERROR_READ_ACTION_TYPE;
    
    int action_type_num;
    if ((action_type_num = check_action_type(action_type)) > DIV)
        return action_type_num;
    
    if (action_type_num == OUT)
        if ((rc = number_out()))
            return rc; 

    if (action_type_num == SQR)
        if ((rc = number_sqr()))
            return rc; 
    
    if (action_type_num == MUL)
        if ((rc = numbers_mul()))
            return rc;
    
    if (action_type_num == DIV)
        if ((rc = numbers_div()))
            return rc;
        
    return EXIT_SUCCESS;
}