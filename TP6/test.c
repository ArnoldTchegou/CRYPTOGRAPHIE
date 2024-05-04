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


int main(){
	printf("********Vulnérabilité 1 ******\n");
	printf("periode du PRNG: %d\n", find_period());
	printf("********Vulnérabilité 3 ******\n");
	find_challenge();
}
