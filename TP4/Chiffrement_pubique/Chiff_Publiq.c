//ce fichier se compile à l'aide du makefile
#include <stdio.h>
#include <stdint.h>

uint32_t seed = 2;

uint32_t multMod(uint32_t a, uint32_t b, uint32_t n){
	return (a*b)%n;
}

uint32_t square_mod_multiply(uint32_t m, uint32_t e, uint32_t n){
	uint32_t r = 1;
	while(e != 0){
		if((e&1) == 1){
			r = multMod(m, e, n);
		}
		m = multMod(m, m, n);
		e = e>>1;
	}
	return r;
}

uint32_t prng(uint32_t a, uint32_t b, uint32_t n){
	return (multMod(a, seed, n) + b)%n;
}

int main(){
	uint32_t n = 25;
	//uint32_t g = 237;
	uint32_t a = 16;
	uint32_t b = 10;
	//uint32_t n1 = (1<<16) - 1;
	//uint32_t e = prng(a, b,n1);
	//uint32_t g_arnold = square_mod_multiply(g, e, n);
	//uint32_t public_key_chakir = 0xcfdab50d;
	//uint32_t private_key = square_mod_multiply(public_key_chakir, e, n);

	//printf("g_arnold= %X\n", g_arnold);
	//printf("private_key = %X\n", private_key);
	for (int i=0; i<50; i++){
		seed = prng(a, b, n);
		printf("%X\n", seed);
	}
	
}
