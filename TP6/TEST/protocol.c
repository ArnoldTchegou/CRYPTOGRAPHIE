#include "aes.h"
#include "protocol.h"
#include "exponentiation.h"


void broadcast_publickey(char* file_name, uint32_t public_key) {
    if (access(file_name, F_OK) == 0) {
        return;
    } else {
        FILE *fptr = fopen(file_name, "w");
        if (fptr == NULL) {
            printf("Could not read file\n");
            exit(1);
        }
        fprintf(fptr, "%X", public_key);
        fclose(fptr);
    }
}

uint32_t get_publickey_by_filename(char* file_name) {
    
    FILE *fptr = fopen(file_name, "r");

    if (fptr == NULL){
        printf("Error: could not open file %s", file_name);
        exit(1);
    }
    char buffer[4];
    fgets(buffer, 4, fptr);
    fclose(fptr);

    return buffer[0] ^ (buffer[1] << 8) ^ (buffer[2] << 16) ^ (buffer[3] << 24);
}


void create_shared_aes_key_and_encrypt_challenge(uint8_t aes_key[16],
                                                 uint32_t internal_secretkey, 
                                                 uint32_t external_publickey, 
                                                 uint32_t seed_table[1024],
                                                 uint8_t *text, size_t text_len) {

    uint32_t shared_key = square_and_multiply(external_publickey, internal_secretkey);
    

    size_t seed_index = (shared_key & 0x3ff);
   
    for (size_t i=0; i<4; i++) {
        for (size_t j=0; j<4; j++) {
            aes_key[i*4+j] = (seed_table[seed_index + i] >> (8*j)) & 0xFF;
        }
    }
    FILE *fptr = fopen("transcript.out", "w");
    if (fptr == NULL) {
        printf("Could not read file\n");
        exit(1);
    }
    fprintf(fptr, "seed_table: %X\n", seed_table[seed_index]);
    
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, aes_key, 16);
    AES_ECB_encrypt_buffer(&ctx, text, text_len);
    fprintf(fptr, "Encrypted challenge: ");
    for (size_t i=0; i<text_len; i++) {
        fprintf(fptr, "%X", text[i]);
    }
    fprintf(fptr, "\n");
    fclose(fptr);
}


void secure_channel_com(uint8_t *shared_key,
                        size_t shared_key_length,
                        uint8_t *buffer,
                        size_t length, 
                        uint8_t *IV) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, shared_key, shared_key_length, IV);
    AES_CBC_encrypt_buffer(&ctx, buffer, length);
    FILE *fptr = fopen("secure_com.out", "w");
    if (fptr == NULL) {
        printf("Could not read file\n");
        exit(1);
    }
    fprintf(fptr, "Ciphertext: ");
    for (size_t i=0; i<16; i++) {
        fprintf(fptr, "%X", buffer[i]);
    }
    fprintf(fptr, "\n");
    fclose(fptr);
}