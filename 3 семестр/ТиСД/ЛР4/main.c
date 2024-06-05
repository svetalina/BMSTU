#include "head.h" 

int main(void)
{
    setbuf(stdout, NULL);
    
    int rc;
    int stack_type;

    if ((rc = read_stack_type(&stack_type)))
        return rc;

    if (stack_type == 1)
        rc = stack_array();
    
    if (stack_type == 2)
        rc = stack_list();
    
    if (stack_type == 3)
        rc = comparison_stacks();
    
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}