#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "head.h"

#define ERROR_ARGC 1
#define ERROR_FILE 2

int MODE;
FILE* file_in;
FILE* file_out;
int LEFT[17][32], RIGHT[17][32];
int IPtext[64];
int EXPtext[48];
int XORtext[48];
int X[8][6];
int X2[32];
int R[32];
int key56bit[56];
int key48bit[17][48];
int IV[64];
int CIPHER[64];
int ENCRYPTED[64];
int XorTextIV[64];

//Convert Char and Bits
void convertToBinary(int n)
{
    int k, m;
    for (int i = 7; i >= 0; i--)
    {
        m = 1 << i;
        k = n & m;
 
        if (k == 0)
            fprintf(file_out, "0");
        else 
            fprintf(file_out, "1");
    }
}
 
int convertCharToBit()
{

    file_out = fopen("_input_bits.txt", "wb+");
    
	char ch;
	fseek(file_in, 0, SEEK_SET);
	while ((ch = getc(file_in)) != EOF)
		convertToBinary(ch);
    
	fclose(file_out);
}

int convertIntToBits(int value)
{
    int k, j, m;
    static int i;
 
    if (i % 32 == 0)
        i = 0;
 
    for (j = 3; j >= 0; j--)
    {
        m = 1 << j;
        k = value & m;
        if (k == 0)
            X2[3 - j + i] = '0' - 48;
        else 
            X2[3 - j + i] = '1' - 48;
    }
 
    i = i + 4;
}

void convertToBits(int ch[])
{
    int value = 0;
    for (int i = 7; i >= 0; i--) {
        value += (int)pow(2, i) * ch[7 - i];
    }
	
    fprintf(file_out, "%c", value);
}
 
int bittochar(int text[], int end)
{
	if (MODE == 0)
		file_out = fopen("_encrypt.txt", "ab+");
	if (MODE == 1)
		file_out = fopen("_decrypt.txt", "ab+");
	
	for (int i = 0; i < end; i = i + 8)
        convertToBits(&text[i]);
    
	fclose(file_out);
}

//Keys
int key64to56(int pos, int text)
{
    for (int i = 0; i < 56; i++)
        if (PC1[i] == pos + 1)
            return key56bit[i] = text;
}

int key56to48(int round, int pos, int text)
{
    for (int i = 0; i < 56; i++)
        if (PC2[i] == pos + 1)
            return key48bit[round][i] = text;
}
 
void key64to48(unsigned int key[])
{
    int k, backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];
 
    for (int i = 0; i < 64; i++)
        key64to56(i, key[i]);
	
	for (int i = 0; i < 28; i++)
		C[0][i] = key56bit[i];
	for (int i = 28; i < 56; i++)
		D[0][i - 28] = key56bit[i];
 
    for (int i = 1; i < 17; i++)
    {
        int shift = SHIFTS[i - 1];
 
        for (int j = 0; j < shift; j++) 
            backup[i - 1][j] = C[i - 1][j];
        for (int j = 0; j < (28 - shift); j++)
            CD[i][j] = C[i][j] = C[i - 1][j + shift];
        for (int j = 28 - shift, k = 0; j < 28; j++)
            CD[i][j] = C[i][j] = backup[i - 1][k++];
 
        for (int j = 0; j < shift; j++)
            backup[i - 1][j] = D[i - 1][j];
        for (int j = 0; j < (28 - shift); j++)
            CD[i][28 + j] = D[i][j] = D[i - 1][j + shift];
        for (int j = 28 - shift, k = 0; j < 28; j++)
            CD[i][28 + j] = D[i][j] = backup[i - 1][k++];
    }
 
    for (int i = 1; i < 17; i++)
        for (int j = 0; j < 56; j++)
            key56to48(i, j, CD[i][j]);
}
 
void createKeys()
{
    FILE* pt = fopen("key.txt", "rb");
    unsigned int key[64];
    int ch, i = 0;
 
	while ((ch = getc(pt)) != EOF)
		key[i++] = ch - '0';
	 
    key64to48(key);

    fclose(pt);
}

void readIV()
{
	file_in = fopen("IV.txt", "rb");
	
	int ch;
	for (int i = 0; i < 64; i++)
	{
		ch = getc(file_in);
		IV[i] = ch - '0';
	}
	
	fclose(file_in);
}

//Encryption-Decryption
int initialPermutation(int pos, int text)
{
    for (int i = 0; i < 64; i++)
        if (IP[i] == pos + 1)
            return IPtext[i] = text;;
}
 
void expansionFunction(int pos, int text)
{
    for (int i = 0; i < 48; i++)
        if (E[i] == pos + 1)
            EXPtext[i] = text;
}

int XOR(int a, int b) {
    return (a ^ b);
}
 
int F1(int i)
{
    int r, c, b[6];
 
    for (int j = 0; j < 6; j++)
        b[j] = X[i][j];
 
    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];
 
    return S[i][r][c];
}
 
int SBox(int XORtext[])
{
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 6; j++)
            X[i][j] = XORtext[k++];
 
    for (int i = 0; i < 8; i++)
        convertIntToBits(F1(i));
}
 
int PBox(int pos, int text)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if (P[i] == pos + 1) {
            break;
        }
    }
    R[i] = text;
}
 
void cipher(int round)
{
    for (int i = 0; i < 32; i++)
        expansionFunction(i, RIGHT[round - 1][i]);
 
    for (int i = 0; i < 48; i++)
        XORtext[i] = XOR(EXPtext[i], key48bit[round][i]);

    SBox(XORtext);
 
    for (int i = 0; i < 32; i++)
        PBox(i, X2[i]);
 
    for (int i = 0; i < 32; i++)
        RIGHT[round][i] = XOR(LEFT[round - 1][i], R[i]);
}
 
int finalPermutation(int pos, int text)
{
    for (int i = 0; i < 64; i++)
        if (FP[i] == pos + 1)
            return ENCRYPTED[i] = text;
}
 
void Encryption(int plain[])
{
    for (int i = 0; i < 64; i++)
        initialPermutation(i, plain[i]);
 
    for (int i = 0; i < 32; i++)
        LEFT[0][i] = IPtext[i];
    for (int i = 32; i < 64; i++)
        RIGHT[0][i - 32] = IPtext[i];
 
    for (int i = 1; i < 17; i++)
    {
        cipher(i);
 
        for (int j = 0; j < 32; j++)
            LEFT[i][j] = RIGHT[i - 1][j];
    }
 
    for (int i = 0; i < 64; i++)
    {
        if (i < 32)
            CIPHER[i] = RIGHT[16][i];
        else
            CIPHER[i] = LEFT[16][i - 32];
        finalPermutation(i, CIPHER[i]);
    }
	
	for (int i = 0; i < 64; i++)
		IV[i] = ENCRYPTED[i]; 
}

void encrypt(int num_block)
{
	if (MODE == 0)
	{
		file_in = fopen("_input_bits.txt", "rb");
		file_out = fopen("_encrypt_bits.txt", "ab+");
	}
	
	if (MODE == 1)
	{
		file_in = fopen("_encrypt_bits.txt", "rb");
		file_out = fopen("_decrypt_bits.txt", "ab+");
	}
 
    int plain[num_block * 64];
	int plainXor[num_block * 64];
	for (int i = 0; i < num_block * 64; i++)
		plain[i] = 0;
	
	int ch, i = 0;
	
	fseek(file_in, 0, SEEK_SET);
	while ((ch = getc(file_in)) != EOF)
		plain[i++] = ch - 48;
 
    for (int i = 0; i < num_block; i++)
	{
        Encryption(IV);
		
		for (int j = 0; j < 64; j++)
		{
			plainXor[i * 64 + j] = XOR(plain[i * 64 + j], IV[j]);
			fprintf(file_out, "%d", plainXor[i * 64 + j]);
		}
	}

    fclose(file_in);
	fclose(file_out);
	
	bittochar(plainXor, num_block * 64);
}
 
int main(int argc, char *argv[]) 
{
	int error = 0;	
	
	if (argc != 2)
        return error = ERROR_ARGC;
	
	if ((file_in = fopen(argv[1], "r")) == NULL)
        return error = ERROR_FILE;
	
	fseek(file_in, 0, SEEK_END);
	int size = ftell(file_in);
	
	int num_block;
	if (size % 8 == 0)
		num_block = size / 8;
	else
		num_block = size / 8 + 1;
	
	convertCharToBit(size);
	
	fclose(file_in);
    
	createKeys();
	
	readIV();
	MODE = 0;
	encrypt(num_block);
	
	readIV();
	MODE = 1;
    encrypt(num_block);
		
    return error;
}
