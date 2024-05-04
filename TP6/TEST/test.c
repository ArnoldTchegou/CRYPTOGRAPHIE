#include "aes.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "protocol.c"
#include "exponentiation.c"
#include "rng.c"
#include <getopt.h>
#include <stdint.h>

uint32_t g = 10;
uint32_t seed_table[1024];

void init_seed_table(){
    // Init PRNG
    seed = 0;
    uint32_t a = 16;
    uint32_t b = 10;
    uint32_t m = 25;
    // init seed table
    for (size_t i = 0; i < 1024; i++) {
        prng(a, b, m);
        seed_table[i] = seed;
    }
}
//VULN1
int find_period(){
	int period = 0;
	FILE *fptr;
	fptr = fopen("prng.out", "r");
	uint32_t* first = malloc(sizeof(uint32_t));
	uint32_t* tab = malloc(sizeof(uint32_t));
	fscanf(fptr, "%X", first);
	fscanf(fptr, "%X", tab);
	if(*first!=*tab){
		period++;
	}
	
	while(!feof(fptr)&&(*first!=*tab)){
		fscanf(fptr, "%X", tab);
		period++;	
	}
	return period;
	fclose(fptr);
}
//VULN2
void reverse_sqr_and_mult(char* tab){
	FILE *fich = fopen("reverse_sqr_and_mult.out", "a");
        if (fich == NULL) {
		printf("Could not read file\n");
		exit(1);
        }
        while(*tab!='\0'){
        	if (*tab == '1'){
        		fprintf(fich, "1");
        		tab++;
        	}
        	else if (*tab == '0'){
        		fprintf(fich, "0");
        	}
        	tab++;
        }
        fprintf(fich, "\n");
        fclose(fich);
}

void inverserChaine(char *chaine) {
    int longueur = strlen(chaine);
    int debut = 0;
    int fin = longueur - 1;
    while (debut < fin) {
        // Échange des caractères aux positions debut et fin
        char temp = chaine[debut];
        chaine[debut] = chaine[fin];
        chaine[fin] = temp;

        // Déplacement des indices vers le centre de la chaîne
        debut++;
        fin--;
    }
}

void find_pub_key(){
	char alice_pub_key[64];
	char bob_pub_key[64];
	FILE *fptr = fopen("sqr_and_mult.out", "r");
        if (fptr == NULL) {
		printf("Could not read file\n");
		exit(1);
        }
        fgets(alice_pub_key, 64, fptr);
        fgets(bob_pub_key, 64, fptr);
        fclose(fptr);
        reverse_sqr_and_mult(alice_pub_key);
        reverse_sqr_and_mult(bob_pub_key); 
        fptr = fopen("reverse_sqr_and_mult.out", "r"); 
        if (fptr == NULL) {
		printf("Could not read file\n");
		exit(1);
        }
        fgets(alice_pub_key, 64, fptr);
        fgets(bob_pub_key, 64, fptr);
        inverserChaine(alice_pub_key);
        inverserChaine(bob_pub_key);
        printf("clé secrete de Bob: %s\n",alice_pub_key);
        printf("clé secrete d'Alice: %s\n",bob_pub_key);
        fclose(fptr);
}
//VULN3
void find_challenge(){
        struct AES_ctx ctx;
        uint8_t key[16];
        uint32_t seed_values[4] = {0x3B468,0x1A0A8,0x375E8,0x1DF28};
	for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
		key[i*4+j] = (seed_values[i] >> (8*j)) & 0xFF;
	    }
	}
        AES_init_ctx(&ctx,key,16);
        //Preparation texte chiffré
        uint8_t buffer[16] = {0x06,0x47,0x55,0x75,0x60,0x42,0xA4,0xE0,0xB2,0xF9,0x17,0x86,0xD4,0x9B,0x61,0x6C};    
        AES_ECB_decrypt_buffer(&ctx,buffer,16);
        // Affichage du texte chiffré
        for(int i=0;i<sizeof(buffer);i++)
        {
                printf("%x", buffer[i]);
        }
        printf("\n");
}

//VULN4
void redef_create_shared_aes_key_and_encrypt_challenge(uint8_t aes_key[16],
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
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, aes_key, 16);
    AES_ECB_encrypt_buffer(&ctx, text, text_len);
    for (size_t i=0; i<text_len; i++) {
        fprintf(fptr, "%X", text[i]);
    }
    fclose(fptr);
}

void create_shared_aes_key_and_decrypt_challenge(uint8_t aes_key[16],
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
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, aes_key, 16);
    AES_ECB_decrypt_buffer(&ctx, text, text_len);
}

void decipher_secure_channel_com(uint8_t *shared_key,
                        size_t shared_key_length,
                        uint8_t *buffer,
                        size_t length, 
                        uint8_t *IV) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, shared_key, shared_key_length, IV);
    AES_CBC_decrypt_buffer(&ctx, buffer, length);
    AES_ECB_decrypt_buffer(&ctx, buffer, length);
}

void send_message_to_Bob_by_Eve(){
	//preparation de la clé publique de Bob
	uint32_t bob_secret_key = 0x47472121;
	uint32_t bob_public_key = square_and_multiply(g, bob_secret_key);
	broadcast_publickey("bob_pubkey.out", bob_public_key);
	
	//préparation de la clé publique de Eve et ecriture dans le fichier alice_pubkey.out
	uint32_t Eve_secret_key = 0x45766521;
	uint32_t Eve_public_key = square_and_multiply(g, Eve_secret_key);
	broadcast_publickey("alice_pubkey.out", Eve_public_key);
	
	//Eve initie le protocole en créant une clé partagée et en chiffrant le challenge qu'elle renvoie à Bob dans transcript.out.
	uint8_t shared_key_Eve[16];
	uint8_t challenge[16] = {0x53, 0x65, 0x6E, 0x64, 0x20, 0x31, 0x30, 0x30, 0x24, 0x20, 0x74, 0x6F, 0x20, 0x45, 0x76, 0x65};
	size_t challenge_len = 16;
	uint32_t external_pub_key;
	printf("Challenge_initiale: ");
    	for(int i=0;i<16;i++)
	{
	       printf("%X",challenge[i]);
	}
	printf("\n");
	
	//Eve lit la clé publique de bob dans le fichier bob_pubkey.out
	FILE *fptr = fopen("bob_pubkey.out", "r");
	if (fptr == NULL) {
		printf("Could not read file\n");
		exit(1);
	}
	fscanf(fptr, "%X", &external_pub_key);
	
	//Eve chiffre le challenge à l'aide de la clé publique de bob et de sa propre clé secrète
	redef_create_shared_aes_key_and_encrypt_challenge(shared_key_Eve, Eve_secret_key, external_pub_key, seed_table, challenge, challenge_len);
	printf("Challenge_chiffré: ");
    	for(int i=0;i<16;i++)
	{
	       printf("%X",challenge[i]);
	}
	printf("\n");
	
	//Eve chiffre le message Send 100$ to Eve et l'envoie à Bob
	char str_transaction[] = "Send 100$ to Eve";
	uint8_t transaction[16];
	for (size_t i=0; i<16; i++) {
		transaction[i] = str_transaction[i];
	}
	printf("message à chiffré: ");
	for (size_t i=0; i<16; i++) {
		printf("%X", transaction[i]);
	}
	printf("// Send 100$ to Eve\n");
	secure_channel_com(shared_key_Eve, 16, transaction, 16, challenge);
	printf("message chiffré: ");
	for (size_t i=0; i<16; i++) {
		printf("%X", transaction[i]);
	}
	printf("\n");
	
	
	//Bob déchiffre le messsage
	uint8_t shared_key_Bob[16];
	uint8_t decrypted_challenge[16];
	memcpy(decrypted_challenge, challenge, 16);  //Bob recupère le challenge
	uint32_t external_pub_key_eve;
	fptr = fopen("alice_pubkey.out", "r");  //Bob recupère la fausse clé publique d'alice pour dechiffrer le challenge
	if (fptr == NULL) {
		printf("Could not read file\n");
		exit(1);
	}
	fscanf(fptr, "%X", &external_pub_key_eve);
	create_shared_aes_key_and_decrypt_challenge(shared_key_Bob, bob_secret_key, external_pub_key_eve, seed_table, decrypted_challenge, challenge_len);
	//Bob dechiffre le message envoyé
	decipher_secure_channel_com(shared_key_Bob, 16, transaction, 16, decrypted_challenge);
	printf("message déchiffré: ");
	for (size_t i=0; i<16; i++) {
		printf("%X",transaction[i]);
	}
	printf("\n");
	fclose(fptr);
}
int main(){
	printf("********Vulnérabilité 1 ******\n");
	printf("periode du PRNG: %d\n", find_period());
	printf("********Vulnérabilité 2 ******\n");
	find_challenge();
	printf("********Vulnérabilité 3 ******\n");
	find_pub_key();
	printf("********Vulnérabilité 4 ******\n");
	send_message_to_Bob_by_Eve();
}
