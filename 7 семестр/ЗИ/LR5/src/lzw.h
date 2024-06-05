#include <limits.h>

#define MIN_CODE_LEN 9                  
#define MAX_CODE_LEN 20                 

#define FIRST_CODE (1 << CHAR_BIT)
#define MAX_CODES  (1 << MAX_CODE_LEN)

#define CURRENT_MAX_CODES(bits) ((unsigned int)(1 << (bits)))

int LZWEncodeFile(FILE *fpIn, FILE *fpOut);
int LZWDecodeFile(FILE *fpIn, FILE *fpOut);
