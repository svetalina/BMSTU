#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lzw.h"
#include "bitfile.h"

typedef struct dict_node_t
{
    unsigned int codeWord;     
    unsigned char suffixChar;   
    unsigned int prefixCode;    

    struct dict_node_t *left;   
    struct dict_node_t *right; 
} dict_node_t;


dict_node_t *MakeNode( unsigned int codeWord, unsigned int prefixCode, unsigned char suffixChar);
void FreeTree(dict_node_t *node);
dict_node_t *FindDictionaryEntry(dict_node_t *root, int unsigned prefixCode, unsigned char c);
unsigned int MakeKey(unsigned int prefixCode, unsigned char suffixChar);
int PutCodeWord(bit_file_t *bfpOut, int code, unsigned char codeLen);

int LZWEncodeFile(FILE *fpIn, FILE *fpOut)
{
    bit_file_t *bfpOut;                

    unsigned int code;                  
    unsigned char currentCodeLen;       
    unsigned int nextCode;             
    int c;                             

    dict_node_t *dictRoot, *node;           

    bfpOut = MakeBitFile(fpOut, BF_WRITE);

    dictRoot = NULL;

    currentCodeLen = MIN_CODE_LEN;

    nextCode = FIRST_CODE;

    c = fgetc(fpIn);

    if (EOF == c) return -1;
    else code = c; 

    if ((c = fgetc(fpIn)) != EOF)
    {
        dictRoot = MakeNode(nextCode, code, c);
        
        nextCode++;

        PutCodeWord(bfpOut, code, currentCodeLen);
		
        code = c;
    }

    while ((c = fgetc(fpIn)) != EOF)
    {
        node = FindDictionaryEntry(dictRoot, code, c);

        if ((node->prefixCode == code) && (node->suffixChar == c))
            code = node->codeWord;
        else
        {
            if (nextCode < MAX_CODES)
            {
                dict_node_t *tmp;

                tmp = MakeNode(nextCode, code, c);

                nextCode++;

                if (MakeKey(code, c) < MakeKey(node->prefixCode, node->suffixChar))
                    node->left = tmp;
                else
                    node->right = tmp;
            }

            while ((code >= (CURRENT_MAX_CODES(currentCodeLen) - 1)) && (currentCodeLen < MAX_CODE_LEN))
            {
                PutCodeWord(bfpOut, (CURRENT_MAX_CODES(currentCodeLen) - 1), currentCodeLen);
                currentCodeLen++;
            }

            PutCodeWord(bfpOut, code, currentCodeLen);

            code = c;
        }
    }

    PutCodeWord(bfpOut, code, currentCodeLen);
    BitFileToFILE(bfpOut);
    FreeTree(dictRoot);

    return 0;
}

unsigned int MakeKey(unsigned int prefixCode, unsigned char suffixChar)
{
    unsigned int key;

    key = suffixChar & 0xF0;
    key <<= MAX_CODE_LEN;
	
    key |= (prefixCode << 4);
    key |= (suffixChar & 0x0F);

    return key;
}

dict_node_t *MakeNode(unsigned int codeWord, unsigned int prefixCode, unsigned char suffixChar)
{
    dict_node_t *node;

    node = malloc(sizeof(dict_node_t));

    if (NULL != node)
    {
        node->codeWord = codeWord;
        node->prefixCode = prefixCode;
        node->suffixChar = suffixChar;

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void FreeTree(dict_node_t *node)
{
    if (NULL == node) return;
    if (node->left != NULL) FreeTree(node->left);
    if (node->right != NULL) FreeTree(node->right);
    free(node);
}


dict_node_t *FindDictionaryEntry(dict_node_t *root, int unsigned prefixCode, unsigned char c)
{
    unsigned int searchKey, key;

    if (NULL == root)
        return NULL;

    searchKey = MakeKey(prefixCode, c);  

    while (1)
    {
        key = MakeKey(root->prefixCode, root->suffixChar);

        if (key == searchKey)
            return root;
        else if (searchKey < key)
        {
            if (NULL != root->left) root = root->left;
            else return root;
        }
        else
        {
            if (NULL != root->right) root = root->right;
            else return root;
        }
    }
}

int PutCodeWord(bit_file_t *bfpOut, int code, unsigned char codeLen)
{
    return BitFilePutBitsNum(bfpOut, &code, codeLen, sizeof(code));
}
