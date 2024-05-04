#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


const uint8_t SBox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};

const uint8_t MulBox[16]={
	0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02
};

uint32_t aes128_extended_key[4*11] = {
    0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,
    0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605,
    0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,
    0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b,
    0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00,
    0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,
    0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd,
    0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f,
    0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
    0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e,
    0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6
};



uint8_t GMul(uint8_t a, uint8_t b) {
	uint8_t p = 0;
	while (a != 0 && b != 0) {
        if (b & 1) {
            p ^= a;
        }
        if (a & 0x80) {
            a = (a << 1) ^ 0x11b;
        }
        else {
            a <<= 1; 
        }
        b >>= 1;
	}
	return p;
}

void AddRoundKey (uint32_t state[4], uint32_t extended_key[4*11], size_t round) {
    for (size_t i=0; i<4; i++) {
        state[i] ^= extended_key[4*round + i];
    }
}
//corrigé
void MixColumns(uint32_t aes_state[4]) {
    uint32_t s0, s1, s2, s3;
    uint8_t o0, o1, o2, o3;
    uint8_t t0, t1, t2, t3;
    uint32_t state[4];
    state[0] = aes_state[0];
    state[1] = aes_state[1];
    state[2] = aes_state[2];
    state[3] = aes_state[3];
	
    for (size_t i=0; i<4; i++) {
        s0 = state[0]&0xFF000000;
        s1 = state[1]&0xFF000000;
        s2 = state[2]&0xFF000000;
        s3 = state[3]&0xFF000000;
        t0 = (s0>>24)&0xFF;
        t1 = (s1>>24)&0xFF;
        t2 = (s2>>24)&0xFF;
        t3 = (s3>>24)&0xFF;
        o0 = GMul(t0, MulBox[4*i]) ^ GMul(t1, MulBox[1+4*i]) ^ GMul(t2, MulBox[2+4*i]) ^ GMul(t3, MulBox[3+4*i]);
        s0 = state[0]&0xFF0000;
        s1 = state[1]&0xFF0000;
        s2 = state[2]&0xFF0000;
        s3 = state[3]&0xFF0000;
        t0 = (s0>>16)&0xFF;
        t1 = (s1>>16)&0xFF;
        t2 = (s2>>16)&0xFF;
        t3 = (s3>>16)&0xFF;
        o1 = GMul(t0, MulBox[4*i]) ^ GMul(t1, MulBox[1+4*i]) ^ GMul(t2, MulBox[2+4*i]) ^ GMul(t3, MulBox[3+4*i]);
        s0 = state[0]&0xFF00;
        s1 = state[1]&0xFF00;
        s2 = state[2]&0xFF00;
        s3 = state[3]&0xFF00;
        t0 = (s0>>8)&0xFF;
        t1 = (s1>>8)&0xFF;
        t2 = (s2>>8)&0xFF;
        t3 = (s3>>8)&0xFF;
        o2 = GMul(t0, MulBox[4*i]) ^ GMul(t1, MulBox[1+4*i]) ^ GMul(t2, MulBox[2+4*i]) ^ GMul(t3, MulBox[3+4*i]);
        t0 = state[0]&0xFF;
        t1 = state[1]&0xFF;
        t2 = state[2]&0xFF;
        t3 = state[3]&0xFF;
        o3 = GMul(t0, MulBox[4*i]) ^ GMul(t1, MulBox[1+4*i]) ^ GMul(t2, MulBox[2+4*i]) ^ GMul(t3, MulBox[3+4*i]);
        aes_state[i] = (o0 << 24) ^ (o1 << 16) ^ (o2 << 8) ^ o3;
    }
}
//corrigé
void ShiftRows(uint32_t state[4]) {
    uint32_t s0 = state[0];
    uint32_t s1 = state[1];
    uint32_t s2 = state[2];
    uint32_t s3 = state[3];

    state[0] = (s0 & 0xFF000000) ^ (s0 & 0xFF0000) ^ (s0 & 0xFF00) ^ (s0 & 0xFF);
    state[1] = ((s1 & 0xFF000000)>>24) ^ ((s1 & 0xFF0000)<<8) ^ ((s1 & 0xFF00)<<8) ^ ((s1 & 0xFF)<<8);
    state[2] = ((s2 & 0xFF000000)>>16) ^ ((s2 & 0xFF0000)>>16) ^ ((s2 & 0xFF00)<<16) ^ ((s2 & 0xFF)<<16);
    state[3] = ((s3 & 0xFF000000)>>8)^ ((s3 & 0xFF0000)>>8) ^ ((s3 & 0xFF00)>>8) ^ ((s3 & 0xFF)<<24);

}

//corrigé
void SubBytes(uint32_t state[4]) {
    uint8_t s0, s1, s2, s3;
    for (size_t i=0; i<4; i++) {
        s0 = state[i] & 0xFF;
        s1 = (state[i] & 0xFF00) >> 8;
        s2 = (state[i] & 0xFF0000) >> 16;
        s3 = state[i] >> 24;
        state[i] = (SBox[s3] << 24) ^ (SBox[s2] << 16) ^ (SBox[s1] << 8) ^ SBox[s0];
    }
}

//corrigé
void aes128_encryption(uint32_t aes128_state[4], uint32_t aes128_extendedkey[4*11]) {
    // Initial AddRoundKey
    AddRoundKey(aes128_state, aes128_extended_key, 0);
    // AES Round Functions
    for (size_t i=1; i<10; i++) {
        SubBytes(aes128_state);
        ShiftRows(aes128_state);
        MixColumns(aes128_state);
        AddRoundKey(aes128_state, aes128_extended_key, i);
    }
    // Last Round
    SubBytes(aes128_state);
    MixColumns(aes128_state);
    AddRoundKey(aes128_state, aes128_extendedkey, 10);
}

void print_state(uint32_t aes_state[4]){
	for(int i=0; i<4; i++){
		printf("\t\t%X\n",aes_state[i]);
	}
}

int main (int argc, char *argv[]) {


    /* Intializes random number generator */
    //time_t t;
    //srand((unsigned) time(&t));

    //uint32_t aes128_state[4] = {0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a}; 
    	uint32_t aes128_state[4] = {
	    0xd4e0b81e,
	    0xbfb44127,
	    0x5d521198,
	    0x30aef1e5,  
	};   

    aes128_encryption (aes128_state, aes128_extended_key);

    // FILE *fptr;
    // fptr = fopen("/path/to/aes.diehard", "a");
    // if (fptr == NULL) {
    //     printf("Could not read file\n");
    //     exit(1);
    // }


    // aes128_state[0] = 0;
    // aes128_state[1] = 0;
    // aes128_state[2] = 0;
    // aes128_state[3] = 0;

    // for (size_t nb_sample=0; nb_sample<1000; nb_sample ++) {    

    //     aes128_encryption (aes128_state, aes128_extended_key);
    //     for (size_t i=0; i<4; i++) {
    //         fprintf(fptr, "%u", aes128_state[i]);
    //     }
    //     fprintf(fptr, "\n");
    //     aes128_state[0] += 1;
    // }

    // fclose(fptr);
        // Initial AddRoundKey
    //printf("Initial\n");
    //print_state(aes128_state);
    //AddRoundKey(aes128_state, aes128_extended_key, 0);
    //printf("extended key\n");
    //print_state(aes128_state);
    //SubBytes(aes128_state);
    //printf("subbyte\n");
    //print_state(aes128_state);
    //ShiftRows(aes128_state);
    //printf("shift row\n");
    //print_state(aes128_state);
    //MixColumns(aes128_state);
    //printf("mixcolum\n");
    print_state(aes128_state);

    return 0;
}
