#include "head.h"

int main(int argc, char **argv)
{
    if (argc < MIN_ARGC)
        return ERROR;
    
    if (0 == strcmp(argv[NUMBER_KEY], "sb"))
        return key_is_sb(argc, argv);
        
    if (0 == strcmp(argv[NUMBER_KEY], "fb"))
        return key_is_fb(argc, argv);
    
    if (0 == strcmp(argv[NUMBER_KEY], "ab"))
        return key_is_ab(argc, argv);
        
    return ERROR;
}
