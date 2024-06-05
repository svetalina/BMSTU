#include <stdio.h>
#include <errno.h>
#include "lzw.h"
#include "bitfile.h"

typedef struct
{
    unsigned char suffixChar;
    unsigned int prefixCode;
} decode_dictionary_t;


decode_dictionary_t dictionary[(MAX_CODES - FIRST_CODE)];

unsigned char DecodeRecursive(unsigned int code, FILE *fpOut);
int GetCodeWord(bit_file_t *bfpIn, unsigned char codeLen);


int LZWDecodeFile(FILE *fpIn, FILE *fpOut)
{
    bit_file_t *bfpIn;              

    unsigned int nextCode, lastCode;                           
    unsigned int code;                  
    unsigned char currentCodeLen;       
    unsigned char c;                    

    bfpIn = MakeBitFile(fpIn, BF_READ);
	
    currentCodeLen = MIN_CODE_LEN;

    nextCode = FIRST_CODE; 

    lastCode = GetCodeWord(bfpIn, currentCodeLen);
    c = lastCode;
    fputc(lastCode, fpOut);

    while ((int)(code = GetCodeWord(bfpIn, currentCodeLen)) != EOF)
    {
        while (((CURRENT_MAX_CODES(currentCodeLen) - 1) == code) && (currentCodeLen < MAX_CODE_LEN))
        {
            currentCodeLen++;
            code = GetCodeWord(bfpIn, currentCodeLen);
        }

        if (code < nextCode)
            c = DecodeRecursive(code, fpOut);
        else
        {
            unsigned char tmp;

            tmp = c;
            c = DecodeRecursive(lastCode, fpOut);
            fputc(tmp, fpOut);
        }

        if (nextCode < MAX_CODES)
        {
            dictionary[nextCode - FIRST_CODE].prefixCode = lastCode;
            dictionary[nextCode - FIRST_CODE].suffixChar = c;
            nextCode++;
        }

        lastCode = code;
    }

    BitFileToFILE(bfpIn);

    return 0;
}


unsigned char DecodeRecursive(unsigned int code, FILE *fpOut)
{
    unsigned char c;
    unsigned char firstChar;

    if (code >= FIRST_CODE)
    {
        c = dictionary[code - FIRST_CODE].suffixChar;
        code = dictionary[code - FIRST_CODE].prefixCode;

        firstChar = DecodeRecursive(code, fpOut);
    }
    else
    {
        c = code;
        firstChar = code;
    }

    fputc(c, fpOut);
    return firstChar;
}

int GetCodeWord(bit_file_t *bfpIn, unsigned char codeLen)
{
    int code = 0;
    int count;

    count = BitFileGetBitsNum(bfpIn, &code, codeLen, sizeof(code));

    if (count < codeLen)
        code = EOF;

    return code;
}
