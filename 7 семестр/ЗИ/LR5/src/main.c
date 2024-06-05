#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lzw.h"

int main(int argc, char *argv[])
{ 
	int encode;
    if (strcmp(argv[1], "-e") == 0) encode = 1;
	if (strcmp(argv[1], "-d") == 0) encode = 0;
	
	FILE* fileIn = fopen(argv[2], "rb");
	FILE* fileOut = fopen(argv[3], "wb");
	
    if (encode)
        LZWEncodeFile(fileIn, fileOut);
    else
        LZWDecodeFile(fileIn, fileOut);

    return 0;
}
