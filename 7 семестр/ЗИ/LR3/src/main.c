#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

#include "head.h"

#define ERROR_ARGC 1
#define ERROR_TEXTFILE 2

int SIZES[3][3] =
{ {16, 10, 176},
  {24, 12, 208},
  {32, 14, 240}
};

int numSize = 0;

int keySize()
{
    return SIZES[numSize][0];
}

int numRounds()
{
    return SIZES[numSize][1];
}

int expandedKeySize()
{
    return SIZES[numSize][2];
}

unsigned char key[32] = { 0 };
unsigned char expandedKey[240];

unsigned char IV[16];
unsigned char text[16];
unsigned char IVxorText[16];
unsigned char encrypted[16] = { 0 };
unsigned char decrypted[16] = { 0 };

int FLAG;

void readKey()
{
    FILE* file = fopen("key.txt", "rb");
	
	fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	switch (fileSize) 
	{
        case 24:
			numSize = 1;
            break;
        case 32:
            numSize = 2;
            break;
    }

    fread(key, 1, fileSize, file);

    fclose(file);
}

void readIV()
{
    FILE* file = fopen("IV.txt", "rb");

    fread(IV, 1, 16, file);

    fclose(file);
}

void readText(FILE *file)
{	
	for (int i = 0; i < 16; i++)
		text[i] = 0;

    fread(text, 1, 16, file);
}

void print()
{
	printf("\nCipher Key (HEX format):\n");
    for (int i = 0; i < keySize(); i++)
        printf("%2.2x%c", key[i], ((i + 1) % keySize()) ? ' ' : '\n');

    printf("\nExpanded Key (HEX format):\n");
    for (int i = 0; i < expandedKeySize(); i++)
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
	
	printf("\nInitialization Vector (HEX format):\n");
    for (int i = 0; i < 16; i++)
        printf("%2.2x%c", IV[i], ((i + 1) % 16) ? ' ' : '\n');

    printf("\nPlaintext (HEX format):\n");
    for (int i = 0; i < 16; i++)
        printf("%2.2x%c", text[i], ((i + 1) % 16) ? ' ' : '\n');
}

void printFile()
{
	FILE *file;
	
	if(FLAG == 0 || FLAG == 1)
	{
		file = fopen("_encrypted.txt", "ab");
			for (int i = 0; i < 16; i++)
				fprintf(file, "%c", encrypted[i]);
			fclose(file);
	}
	
	if(FLAG == 0 || FLAG == 2)
	{		
			file = fopen("_decrypted.txt", "ab");
			for (int i = 0; i < 16; i++)
				fprintf(file, "%c", decrypted[i]);
			fclose(file);
	}
}

int main(int argc, char* argv[])
{
    int error = 0;
	
	if (argc != 3)
		return ERROR_ARGC;
	
	readIV();
	
	readKey();
	expandKey();

	FILE* file = fopen(argv[1], "rb");
	if (file == NULL)
		return ERROR_TEXTFILE;
	
	fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);	
	int numBlock = (fileSize % 16 == 0) ? fileSize / 16 : fileSize / 16 + 1;
	
	if(strcmp(argv[2], "all") == 0)
	{
		FLAG = 0;
	}
	
	if(strcmp(argv[2], "en") == 0)
	{
		FLAG = 1;
	}
	
	if(strcmp(argv[2], "de") == 0)
	{
		FLAG = 2;
	}
    
	int i = 0;
	while (i++ < numBlock)
	{
		printf("\x1b[31\nmБлок текста №%d\n\x1b[0m", i);
		
		readText(file);
		
		for (int i = 0; i < 16; i++)
			IVxorText[i] = text[i] ^ IV[i];
		
		if(FLAG == 0)
		{
			for (int i = 0; i < 16; i++)
				IVxorText[i] = text[i] ^ IV[i];
		
			aes();
			aes_inv();
		
			for (int i = 0; i < 16; i++)
				decrypted[i] = decrypted[i] ^ IV[i];
			
			print();
			printFile();
	
			
			printf("\nEncrypted text (HEX format):\n");
			for (int i = 0; i < 16; i++)
				printf("%2.2x%c", encrypted[i], ((i + 1) % 16) ? ' ' : '\n');
			printf("\nDecrypted text (HEX format):\n");
			for (int i = 0; i < 16; i++)
				printf("%2.2x%c", decrypted[i], ((i + 1) % 16) ? ' ' : '\n');
			
			for (int i = 0; i < 16; i++)
			IV[i] = text[i] ^ encrypted[i];
		}
		
		if(FLAG == 1)
		{
			for (int i = 0; i < 16; i++)
				IVxorText[i] = text[i] ^ IV[i];
		
			aes();
			
			print();
			printFile();
	
			
			printf("\nEncrypted text (HEX format):\n");
			for (int i = 0; i < 16; i++)
				printf("%2.2x%c", encrypted[i], ((i + 1) % 16) ? ' ' : '\n');
			
			for (int i = 0; i < 16; i++)
			IV[i] = text[i] ^ encrypted[i];
		}
		
		if(FLAG == 2)
		{	
			for (int i = 0; i < 16; i++)
				encrypted[i] = text[i];
			
			aes_inv();
		
			for (int i = 0; i < 16; i++)
				decrypted[i] = decrypted[i] ^ IV[i];
			
			for (int i = 0; i < 16; i++)
				IV[i] = decrypted[i] ^ text[i];
			
			print();
			printFile();
	

			printf("\nDecrypted text (HEX format):\n");
			for (int i = 0; i < 16; i++)
				printf("%2.2x%c", decrypted[i], ((i + 1) % 16) ? ' ' : '\n');
		}
	}

	fclose(file);
    return 0;
}

//KEYS
void expandKey()
{
    int currentSize = 0;
    int rconIteration = 1;
    unsigned char t[4] = { 0 };

    for (int i = 0; i < keySize(); i++)
        expandedKey[i] = key[i];
    currentSize += keySize();

    while (currentSize < expandedKeySize())
    {
        for (int i = 0; i < 4; i++)
            t[i] = expandedKey[(currentSize - 4) + i];

        if (currentSize % keySize() == 0)
            core(t, rconIteration++);

        if (keySize() == 32 && ((currentSize % keySize()) == 16))
            for (int i = 0; i < 4; i++)
                t[i] = Sbox[t[i]];

        for (int i = 0; i < 4; i++)
        {
            expandedKey[currentSize] = expandedKey[currentSize - keySize()] ^ t[i];
            currentSize++;
        }
    }
}

void core(unsigned char* word, int iteration)
{
    unsigned char tmp = word[0];

    for (int i = 0; i < 3; i++)
        word[i] = word[i + 1];
    word[3] = tmp;

    for (int i = 0; i < 4; ++i)
        word[i] = Sbox[word[i]];

    word[0] = word[0] ^ Rcon[iteration];
}


//ENCRYPTION
void subBytes(unsigned char* state)
{
    for (int i = 0; i < 16; i++)
        state[i] = Sbox[state[i]];
}

void shiftRows(unsigned char* state)
{	
    for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int tmp = state[i];
			for (int k = 0; k < 3; k++)
				state[k * 4 + i] = state[(k + 1) * 4 + i];
			state[12 + i] = tmp;	
		}
	}
}

void mixColumns(unsigned char* state)
{
    unsigned char column[4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            column[j] = state[i * 4 + j];

        mixColumn(column);

        for (int j = 0; j < 4; j++)
            state[i * 4 + j] = column[j];
    }
}

void mixColumn(unsigned char* column)
{    
	unsigned char tmp[4];
    for (int i = 0; i < 4; i++)
        tmp[i] = column[i];

    column[0] = 
		galois_multiplication(tmp[0], 2) ^
		galois_multiplication(tmp[1], 3) ^
		galois_multiplication(tmp[2], 1) ^
		galois_multiplication(tmp[3], 1);

    column[1] = 
		galois_multiplication(tmp[0], 1) ^
		galois_multiplication(tmp[1], 2) ^
		galois_multiplication(tmp[2], 3) ^
		galois_multiplication(tmp[3], 1);

    column[2] = 
		galois_multiplication(tmp[0], 1) ^
		galois_multiplication(tmp[1], 1) ^
		galois_multiplication(tmp[2], 2) ^
		galois_multiplication(tmp[3], 3);
		
	column[3] = 
		galois_multiplication(tmp[0], 3) ^
		galois_multiplication(tmp[1], 1) ^
		galois_multiplication(tmp[2], 1) ^
		galois_multiplication(tmp[3], 2);
}

unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;

    for (counter = 0; counter < 8; counter++)
    {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void addRoundKey(unsigned char* state, unsigned char* roundKey)
{
    for (int i = 0; i < 16; i++)
        state[i] = state[i] ^ roundKey[i];
}

void aes_round(unsigned char* state, unsigned char* roundKey)
{
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, roundKey);
}

void aes()
{  
	unsigned char state[16];

	for (int i = 0; i < 16; i++)
        state[i] = IVxorText[i];
	
	addRoundKey(state, expandedKey);

    for (int i = 1; i < numRounds(); i++)
        aes_round(state, expandedKey + 16 * i);

    subBytes(state);
    shiftRows(state);
    addRoundKey(state, expandedKey + 16 * numRounds());
	
	for (int i = 0; i < 16; i++)
        encrypted[i] = state[i];
}

void invSubBytes(unsigned char* state)
{
    for (int i = 0; i < 16; i++)
        state[i] = RSbox[state[i]];
}

void invShiftRows(unsigned char* state)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int tmp = state[12 + i];
			for (int k = 3; k > 0; k--)
				state[k * 4 + i] = state[(k - 1) * 4 + i];
			state[i] = tmp;	
		}
	}
}

void invMixColumns(unsigned char* state)
{
    unsigned char column[4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            column[j] = state[i * 4 + j];

        invMixColumn(column);

        for (int j = 0; j < 4; j++)
            state[i * 4 + j] = column[j];
    }
}

void invMixColumn(unsigned char* column)
{
    unsigned char tmp[4];

    for (int i = 0; i < 4; i++)
        tmp[i] = column[i];
	
	column[0] = 
		galois_multiplication(tmp[0], 14) ^
		galois_multiplication(tmp[1], 11) ^
		galois_multiplication(tmp[2], 13) ^
		galois_multiplication(tmp[3], 9);

    column[1] = 
		galois_multiplication(tmp[0], 9) ^
		galois_multiplication(tmp[1], 14) ^
		galois_multiplication(tmp[2], 11) ^
		galois_multiplication(tmp[3], 13);
		
	column[2] = 
		galois_multiplication(tmp[0], 13) ^
		galois_multiplication(tmp[1], 9) ^
		galois_multiplication(tmp[2], 14) ^
		galois_multiplication(tmp[3], 11);
		
	column[3] = 
		galois_multiplication(tmp[0], 11) ^
		galois_multiplication(tmp[1], 13) ^
		galois_multiplication(tmp[2], 9) ^
		galois_multiplication(tmp[3], 14);
}

void aes_invRound(unsigned char* state, unsigned char* roundKey)
{
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
    invMixColumns(state);
}

void aes_inv()
{
	unsigned char state[16];
	
	for (int i = 0; i < 16; i++)
        state[i] = encrypted[i];
	
    addRoundKey(state, expandedKey + 16 * numRounds());

    for (int i = numRounds() - 1; i > 0; i--)
        aes_invRound(state, expandedKey + 16 * i);

    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, expandedKey);
	
	for (int i = 0; i < 16; i++)
        decrypted[i] = state[i];
}