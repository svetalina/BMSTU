#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "head.h"

#define ERROR_ARGC 1
#define ERROR_FILE 2
#define WARNING_SYMBOL 3

int main(int argc, char *argv[]) {
	
	int error = 0;	
	
	//FILES
	if (argc != 3)
        return error = ERROR_ARGC;
	
	FILE *file_in = fopen(argv[1], "r");
	FILE *file_out = fopen(argv[2], "w");
	if (file_in == NULL || file_out == NULL)
        return error = ERROR_FILE;
	
	// INIT ENCODER 
    uint8_t alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size_alph = (int)strlen((char*)alphabet);
    encoder_t *encoder = encoder_new(size_alph);
    encoder_set_alphabet(encoder, alphabet);

    // INIT ENIGMA
    int num_rotors = 3;
	int steckbrett[] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int reflector[] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int *rotors[] = {
        (int[]){11, 12, 13, 14, 15, 6, 7, 8, 9, 10, 16, 17, 0, 1, 2, 3, 4, 5, 18, 19, 20, 21, 22, 23, 24, 25},
        (int[]){20, 21, 22, 23, 24, 25, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        (int[]){7, 6, 5, 4, 3, 2, 1, 0, 24, 23, 22, 21, 20, 25, 8, 9, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
    };
    enigma_t *enigma = enigma_new(size_alph, num_rotors);
	enigma_set_steckbrett(enigma, steckbrett);
    enigma_set_reflector(enigma, reflector);
    for (int i = 0; i < num_rotors; ++i) {
        enigma_set_rotor(enigma, i, rotors[i]);
    }
	

    int ch, enc_ch, dec_ch;	
	while ((ch = fgetc(file_in)) != '\n') {	
		if (isalpha(ch)) {
            ch = toupper(ch);
		
			enc_ch = encoder_encode(encoder, (int)ch);
			enc_ch = enigma_encrypt(enigma, enc_ch);
			dec_ch = encoder_decode(encoder, enc_ch);
			
			fputc(dec_ch, file_out);
			putchar(dec_ch);
		}
		else {
			fputc(ch, file_out);
			putchar(ch);
			error = WARNING_SYMBOL;
		}
    }
	
	fputc('\n', file_out);
    
    // FREE
    encoder_free(encoder);
    enigma_free(enigma);
	fclose(file_in);
	fclose(file_out);
	
    return error;
}

// ENCODER
encoder_t *encoder_new(int size_alph) {
    encoder_t *encoder = (encoder_t*)malloc(sizeof(encoder_t));
    if (encoder == NULL)
        return NULL;

    encoder->size_alph = size_alph;
    encoder->alphabet = (uint8_t*)malloc(sizeof(int)*size_alph);
    return encoder;
}

void encoder_free(encoder_t *encoder) {
    free(encoder->alphabet);
    free(encoder);
}

void encoder_set_alphabet(encoder_t *encoder, uint8_t *alphabet) {
    for (int i = 0; i < encoder->size_alph; ++i)
        encoder->alphabet[i] = alphabet[i];
}

int encoder_encode(encoder_t *encoder, int ch) {
	for (int i = 0; i < encoder->size_alph; ++i)
        if (encoder->alphabet[i] == ch)
            return i;
}

int encoder_decode(encoder_t *encoder, int code) {
    return encoder->alphabet[code];
}

// ENIGMA
enigma_t *enigma_new(int size_rotor, int num_rotors) {
    enigma_t *enigma = (enigma_t*)malloc(sizeof(enigma_t));
    if (enigma == NULL)
        return NULL ;

    enigma->size_rotor = size_rotor;
    enigma->num_rotors = num_rotors;
    enigma->counter = 0;

    enigma->steckbrett = (int*)malloc(sizeof(int)*size_rotor);
	enigma->reflector = (int*)malloc(sizeof(int)*size_rotor);
    enigma->rotors = (int**)malloc(sizeof(int*)*num_rotors);

    for (int i = 0; i < num_rotors; ++i)
        enigma->rotors[i] = (int*)malloc(sizeof(int)*size_rotor);

    return enigma;
}

void enigma_free(enigma_t *enigma) {
    for (int i = 0; i < enigma->num_rotors; ++i)
        free(enigma->rotors[i]) ;

    free(enigma->rotors);
    free(enigma->reflector);
	free(enigma->steckbrett);
    free(enigma);
}

void enigma_set_steckbrett(enigma_t *enigma, int *steckbrett) {
    for (int i = 0; i < enigma->size_rotor; ++i)
        enigma->steckbrett[i] = steckbrett[i];
}

void enigma_set_reflector(enigma_t *enigma, int *reflector) {
    for (int i = 0; i < enigma->size_rotor; ++i)
        enigma->reflector[i] = reflector[i];
}

void enigma_set_rotor(enigma_t *enigma, int num, int *rotor) {
    for (int i = 0; i < enigma->size_rotor; ++i)
        enigma->rotors[num][i] = rotor[i];
}

int enigma_encrypt(enigma_t *enigma, int code) {
	
	uint64_t rotor_queue;
    int new_code = code;
	
	new_code = enigma->steckbrett[new_code];

    for (int i = 0; i < enigma->num_rotors; ++i)
        new_code = enigma->rotors[i][new_code];

    new_code = enigma->reflector[new_code];

    for (int i = enigma->num_rotors-1; i >= 0; --i)
        new_code = enigma_rotor_find(enigma, i, new_code);
	
	new_code = enigma->steckbrett[new_code];

    rotor_queue = 1;
    enigma->counter += 1;
    for (int i = 0; i < enigma->num_rotors; ++i) {
        if (enigma->counter % rotor_queue == 0)
            enigma_rotor_shift(enigma, i);

        rotor_queue *= enigma->size_rotor;
    }

    return new_code;
}

void enigma_rotor_shift(enigma_t *enigma, int num) {
    char temp = enigma->rotors[num][enigma->size_rotor-1];
    for (int i = enigma->size_rotor-1; i > 0; --i) 
        enigma->rotors[num][i] = enigma->rotors[num][i-1];

    enigma->rotors[num][0] = temp;
}

int enigma_rotor_find(enigma_t *enigma, int num, int code) {
	for (int i = 0; i < enigma->size_rotor; ++i)
        if (enigma->rotors[num][i] == code) 
            return i;
}