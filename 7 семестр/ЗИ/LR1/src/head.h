// ENCODER
typedef struct encoder_t {
    int size_alph;
    uint8_t *alphabet;
} encoder_t;

encoder_t *encoder_new(int size_alph);
void encoder_free(encoder_t *encoder);

void encoder_set_alphabet(encoder_t *encoder, uint8_t *alphabet);

int encoder_encode(encoder_t *encoder, int ch);
int encoder_decode(encoder_t *encoder, int code);

// ENIGMA
typedef struct enigma_t {
    uint64_t counter;
    int size_rotor;
    int num_rotors;
	int *steckbrett;
    int *reflector;
    int **rotors;
} enigma_t;

enigma_t *enigma_new(int size_rotor, int num_rotors);
void enigma_free(enigma_t *enigma);

void enigma_set_steckbrett(enigma_t *enigma, int *steckbrett);
void enigma_set_reflector(enigma_t *enigma, int *reflector);
void enigma_set_rotor(enigma_t *enigma, int num, int *rotor);

int enigma_encrypt(enigma_t *enigma, int code);

void enigma_rotor_shift(enigma_t *enigma, int num);
int enigma_rotor_find(enigma_t *enigma, int num, int code);