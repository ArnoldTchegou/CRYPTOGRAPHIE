
#include "aes.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // CBC mode, for memset
#include <time.h>
#include "protocol.c"
#include "exponentiation.c"
#include "rng.c"
#include <getopt.h>
#include <stdint.h>
 // // Init Field
    uint32_t g = 10; 
    uint32_t bob_public_key=0x3EEE;

    //Recuperation du message
    uint8_t *get_encrypted_message()
        {
            FILE *file=fopen("secure_com.out","r");
            if(file==NULL)
                {
                    printf("Could not open file\n");
                    exit(1);
                }
        uint8_t* buffer=malloc(16);
        fread(buffer,1,16,file);
        fclose(file);
        return buffer;
        }
    void slicing(uint8_t *A,uint32_t B)
        {
            for(int i=4;i>0;i--)
                {
                    A[4-i]=(B>>8*(i-1)&0xFF);
                }
        }
    void put_encrypted_message(uint8_t *A,char* B)
        {
            FILE *file=fopen(B,"w");
            if(file==NULL)
                {
                    printf("Could not open file\n");
                    exit(1);
                }
            fwrite(A,1,16,file);
            fclose(file);
        }
    void print_bytes(uint8_t *A)
        {
            for(int i=0;i<16;i++)
                {
                    printf("%02x",A[i]);
                }
            printf("\n\n");
        }
int main()
    {
       
    // // Init PRNG
        seed = 15;
     uint32_t a = 7;
    uint32_t b = 9;
    uint32_t m = 45;
        prng(a,b,m);
        // Preparation de la clé public de EVA 
        uint32_t eva_secret_key=seed;
        uint32_t eva_public_key = leaking_square_and_multiply(g, eva_secret_key);
        broadcast_publickey("false_bob_pubkey.out",eva_public_key);
        // Envoie du message d'Alice à Eva en pensant qu'elle envoie à Bob
        uint8_t eva_secret_key_bytes[4];
    slicing(eva_secret_key_bytes,eva_secret_key);
    uint8_t* encrypted_message=get_encrypted_message();
    struct AES_ctx ctx;
    uint8_t iv[16] = {0x43,0x6f,0x72,0x72,0x65,0x63,0x74,0x20,0x63,0x68,0x61,0x6c,0x6c,21,21,0x21};
    AES_init_ctx_iv(&ctx, eva_secret_key_bytes, 16, iv);
    AES_CBC_decrypt_buffer(&ctx,encrypted_message,16);

    //Modification du message
    char* new_message = "Send 100$ to Eva";
    for (size_t i=0; i<16; i++) {
        encrypted_message[i] = new_message[i];
    }

    //Envoie du message à Bob suite à l'interception
    uint8_t bob_public_key_bytes[4];
    slicing(bob_public_key_bytes,bob_public_key);
    AES_init_ctx_iv(&ctx, bob_public_key_bytes, 16, iv);
    AES_CBC_encrypt_buffer(&ctx,encrypted_message,16);
    put_encrypted_message(encrypted_message,"secure_com.out");

   
    printf("Encrypted message: ");
    print_bytes(encrypted_message);

    // Déchiffrement du message chiffré
    uint8_t decrypted_message[16];
    memcpy(decrypted_message, encrypted_message, 16);
    AES_init_ctx_iv(&ctx, bob_public_key_bytes, 16, iv);
    AES_CBC_decrypt_buffer(&ctx, decrypted_message, 16);

    
    printf("Decrypted message: ");
    for (size_t i = 0; i < 16; i++) {
        printf("%02x", decrypted_message[i]);
    }
    printf("\n");
    }