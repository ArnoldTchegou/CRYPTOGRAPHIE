//ce fichier se compile à l'aide du makefile
#include <stdio.h>
#include <stdint.h>
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

const uint8_t rsbox[256] =
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

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

const uint8_t MulBox[16]={
	0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02
};

const uint8_t InvMulBox[16]={
	0x0e, 0x0b, 0x0d, 0x09, 0x09, 0x0e, 0x0b, 0x0d, 0x0d, 0x09, 0x0e, 0x0b, 0x0b, 0x0d, 0x09, 0x0e
};

//chiffrement
void print_state(int tab_len, uint32_t aes_state[tab_len]);
void unit8_extractBlocks(uint32_t* element, uint8_t* blocks, int j);
uint8_t GMul(uint8_t a, uint8_t b);
void AddRoundKey(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11], int k);
void SubBytes(uint32_t aes_state[4]);
void ShiftRows(uint32_t aes_state[4]);
void state_copy(uint32_t aes_state[4], uint32_t aes_state_copy[4]);
void Mixcolumns(uint32_t aes_state[4]);
void Block_Cipher(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11]);
void aes_ecb(uint32_t* message, int m_len, uint32_t aes128_extended_key[4*11]);

//dechiffrement
void InvSubBytes(uint32_t res_state[4]);
void InvAddRoundKey(uint32_t res_state[4], uint32_t aes128_extended_key[4*11], int k);
void InvShiftRows(uint32_t aes_state[4]);
void InvMixcolumns(uint32_t aes_state[4]);
void InvBlock_Cipher(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11]);
void aes_ecb_dechiffrement(uint32_t* message, int m_len, uint32_t aes128_extended_key[4*11]);


int main(){
	uint32_t aes128_state[4] = {
	    0xd4e0b81e,
	    0xbfb44127,
	    0x5d521198,
	    0x30aef1e5,  
	};
    //uint32_t aes128_state[4] = {0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a}; 
    //printf("Initial\n");
    //print_state(4, aes128_state);
    //AddRoundKey(aes128_state, aes128_extended_key, 0);
    //printf("extended key\n");
    //print_state(4, aes128_state);
    //SubBytes(aes128_state);
    //printf("subbyte\n");
    //print_state(4, aes128_state);
    //ShiftRows(aes128_state);
    //printf("shift row\n");
    //print_state(4, aes128_state);
    Mixcolumns(aes128_state);
    printf("mixcolum\n");
    print_state(4, aes128_state);
}

//cette fonction permet d'extraire un block de 8 bits d'un élément de 32 bits
void unit8_extractBlocks(uint32_t* element, uint8_t* blocks, int j) {
        *blocks = (*element >> (j * 8)) & 0xFF;
}

//utilisée pour la mutiplication dans Mixcolumn
uint8_t GMul(uint8_t a, uint8_t b){
    uint8_t p = 0;
    while (a != 0 && b != 0){
        if (b & 1){
            p ^=a;
        }
        if(a & 0x80){
            a = (a << 1) ^ 0x11b;
        }
        else{
            a <<=1;
        }
        b >>=1;
    }
    return p;
}

void AddRoundKey(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11], int k){
	for(int i=0; i<4; i++){
		aes_state[i] = aes_state[i]^aes128_extended_key[4*k + i];
	}
}

void SubBytes(uint32_t aes_state[4]) {
	uint8_t m[4];
	for(int i=0; i<4; i++){
		m[0] = SBox[(aes_state[i])&0xFF];
		m[1] = SBox[(aes_state[i]>>8)&0xFF];
		m[2] = SBox[(aes_state[i]>>16)&0xFF];
		m[3] = SBox[(aes_state[i]>>24)&0xFF];
		aes_state[i] = m[0]^(m[1]<<8)^(m[2]<<16)^(m[3]<<24);
	}
}

void ShiftRows(uint32_t aes_state[4]){
    uint8_t ui8_blocks;
    for(int i =1; i<=3; i++) {
    	int j = 0;
    	while(j < i){
    		unit8_extractBlocks(&aes_state[i], &ui8_blocks, 3);
    		aes_state[i] = aes_state[i] <<8;
    		aes_state[i] = aes_state[i]^ui8_blocks;
    		j++;
    	}       
    }
}

//fait une copy de l'état actuel
void state_copy(uint32_t aes_state[4], uint32_t aes_state_copy[4]){
	for (int i = 0; i < 4; i++){
		aes_state_copy[i] = aes_state[i];
	}
}

//afficher l'état avant et après le chiffrement
void print_state(int tab_len, uint32_t aes_state[tab_len]){
	for(int i=0; i<tab_len; i++){
		printf("\t\t%X\n",aes_state[i]);
	}
}

void Mixcolumns(uint32_t aes_state[4]){
    uint8_t ui8_blocks, substitutedValue = 0x00;
    uint32_t aes_state_copy[4];
    state_copy(aes_state, aes_state_copy);
    for(int j = 3; j >= 0; j--) {
    	for (int k = 0; k < 4; k++){
	    	for (int i = 0; i < 4; i++){
	    	    ui8_blocks = (aes_state_copy[i] >> (j * 8)) & 0xFF;
	    	    // faire GMul
		    substitutedValue = GMul(MulBox[i + 4*k], ui8_blocks)^substitutedValue;
	    	}
	    	 // Mettre à jour la valeur dans aes_state
		aes_state[k] &= ~(0xFF << (j * 8)); // Efface les 8 bits à remplacer
		aes_state[k] ^= (uint32_t)substitutedValue << (j * 8);
		substitutedValue = 0x00;
        }
    }	
}

//la fonction de chiffrement
void Block_Cipher(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11]){

//Initial addk
	AddRoundKey(aes_state, aes128_extended_key, 0);
	
//Round function
	for(int i=1; i<10; i++){
		SubBytes(aes_state);
		ShiftRows(aes_state);
		Mixcolumns(aes_state);
		AddRoundKey(aes_state, aes128_extended_key, i);
	}

//final Round
	SubBytes(aes_state);
	ShiftRows(aes_state);
	AddRoundKey(aes_state, aes128_extended_key, 10);
}

//CHIFFREMENT AES_ECB
void aes_ecb(uint32_t* message, int m_len, uint32_t aes128_extended_key[4*11]){
	int m, n;
	uint32_t tab[4]={0,0,0,0};
//cas m_len<128
	if(m_len<128){
		if(m_len>0&&m_len<32){
			m = 1;
		}
		if(m_len>32&&m_len%32!=0){
			m = m_len/32 + 1;
		}
		if(m_len>=32&&m_len%32==0){
			m = m_len/32;
		}
		if(m == 1){
			tab[0] = *(message);
			Block_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
		}
		if(m == 2){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			Block_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
		}
		if(m == 3){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			tab[2] = *(message + 2);
			Block_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
			*(message + 2) = tab[2];
		}
		if(m == 4){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			tab[2] = *(message + 2);
			tab[3] = *(message + 3);
			Block_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
			*(message + 2) = tab[2];
			*(message + 3) = tab[3];
		}
	}
//cas m_len>=128
	else if(m_len>=128){
		m = m_len/128;
		for(int i=0; i<m; i++){
			tab[0] = *(message + 4*i);
			tab[1] = *(message + 4*i + 1);
			tab[2] = *(message + 4*i + 2);
			tab[3] = *(message + 4*i + 3);
			Block_Cipher(tab, aes128_extended_key);
			*(message + 4*i) = tab[0];
			*(message + 4*i + 1) = tab[1];
			*(message + 4*i + 2) = tab[2];
			*(message + 4*i + 3) = tab[3];	
		}
		
		int m1 = (m_len%128);
		if(m1>0&&m1<32){
			n = 1;
		}
		if(m1>32&&m1%32!=0){
			n = m1/32 + 1;
		}
		if(m1>=32&&m1%32==0){
			n = m1/32;
		}
		if(n == 1){
			tab[0] = *(message + 4*m);
			Block_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0]>>(32-m1);
		}
		if(n == 2){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			Block_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
		}
		if(n == 3){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			tab[2] = *(message + 4*m + 2);
			Block_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
			*(message + 4*m + 2) = tab[2];
		}
		if(n == 4){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			tab[2] = *(message + 4*m + 2);
			tab[3] = *(message + 4*m + 3);
			Block_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
			*(message + 4*m + 2) = tab[2];
			*(message + 4*m + 3) = tab[3];
		}
	}


}

//le dechiffrement

void InvSubBytes(uint32_t res_state[4]){
	uint8_t res[4];
	for(int i=0; i<4; i++){
		res[0] = rsbox[(res_state[i])&0xFF];
		res[1] = rsbox[(res_state[i]>>8)&0xFF];
		res[2] = rsbox[(res_state[i]>>16)&0xFF];
		res[3] = rsbox[(res_state[i]>>24)&0xFF];
		res_state[i] = res[0]^(res[1]<<8)^(res[2]<<16)^(res[3]<<24);
	}
}

void InvAddRoundKey(uint32_t res_state[4], uint32_t aes128_extended_key[4*11], int k){
	for(int i=0; i<4; i++){
		res_state[i] = res_state[i]^aes128_extended_key[4*k + i];
	}

}

void InvShiftRows(uint32_t aes_state[4]){
    uint8_t ui8_blocks;
    for(int i =1; i<=3; i++) {
    	int j = 0;
    	while(j < i){
    		unit8_extractBlocks(&aes_state[i], &ui8_blocks, 0);
    		aes_state[i] = aes_state[i]>>8;
    		aes_state[i] = aes_state[i]^(ui8_blocks<<24);
    		j++;
    	}       
    }
}

void InvMixcolumns(uint32_t aes_state[4]){
    uint8_t ui8_blocks, substitutedValue = 0x00;
    uint32_t aes_state_copy[4];
    state_copy(aes_state, aes_state_copy);
    for(int j = 3; j >= 0; j--) {
    	for (int k = 0; k < 4; k++){
	    	for (int i = 0; i < 4; i++){
	    	    ui8_blocks = (aes_state_copy[i] >> (j * 8)) & 0xFF;
	    	    // faire GMul
		    substitutedValue = GMul(InvMulBox[i + 4*k], ui8_blocks)^substitutedValue;
	    	}
	    	 // Mettre à jour la valeur dans aes_state
		aes_state[k] &= ~(0xFF << (j * 8)); // Efface les 8 bits à remplacer
		aes_state[k] ^= (uint32_t)substitutedValue << (j * 8);
		substitutedValue = 0x00;
        }
    }	
}

void InvBlock_Cipher(uint32_t aes_state[4], uint32_t aes128_extended_key[4*11]){

//Invfinal Round
	InvAddRoundKey(aes_state, aes128_extended_key, 10);
	InvShiftRows(aes_state);
	InvSubBytes(aes_state);
//InvRound function
	for(int i=9; i>0; i--){
		InvAddRoundKey(aes_state, aes128_extended_key, i);
		InvMixcolumns(aes_state);
		InvShiftRows(aes_state);
		InvSubBytes(aes_state);
	}
//InvInitial addk
	InvAddRoundKey(aes_state, aes128_extended_key, 0);
}

//DECHIFFREMENT AES_ECB
void aes_ecb_dechiffrement(uint32_t* message, int m_len, uint32_t aes128_extended_key[4*11]){
	int m, n;
	uint32_t tab[4]={0,0,0,0};
//cas m_len<128
	if(m_len<128){
		if(m_len>0&&m_len<32){
			m = 1;
		}
		if(m_len>32&&m_len%32!=0){
			m = m_len/32 + 1;
		}
		if(m_len>=32&&m_len%32==0){
			m = m_len/32;
		}
		if(m == 1){
			tab[0] = *(message);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
		}
		if(m == 2){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
		}
		if(m == 3){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			tab[2] = *(message + 2);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
			*(message + 2) = tab[2];
		}
		if(m == 4){
			tab[0] = *(message);
			tab[1] = *(message + 1);
			tab[2] = *(message + 2);
			tab[3] = *(message + 3);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message) = tab[0];
			*(message + 1) = tab[1];
			*(message + 2) = tab[2];
			*(message + 3) = tab[3];
		}
	}
//cas m_len>=128
	else if(m_len>=128){
		m = m_len/128;
		for(int i=0; i<m; i++){
			tab[0] = *(message + 4*i);
			tab[1] = *(message + 4*i + 1);
			tab[2] = *(message + 4*i + 2);
			tab[3] = *(message + 4*i + 3);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message + 4*i) = tab[0];
			*(message + 4*i + 1) = tab[1];
			*(message + 4*i + 2) = tab[2];
			*(message + 4*i + 3) = tab[3];	
		}
		
		int m1 = (m_len%128);
		if(m1>0&&m1<32){
			n = 1;
		}
		if(m1>32&&m1%32!=0){
			n = m1/32 + 1;
		}
		if(m1>=32&&m1%32==0){
			n = m1/32;
		}
		if(n == 1){
			tab[0] = *(message + 4*m);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
		}
		if(n == 2){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
		}
		if(n == 3){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			tab[2] = *(message + 4*m + 2);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
			*(message + 4*m + 2) = tab[2];
		}
		if(n == 4){
			tab[0] = *(message + 4*m);
			tab[1] = *(message + 4*m + 1);
			tab[2] = *(message + 4*m + 2);
			tab[3] = *(message + 4*m + 3);
			InvBlock_Cipher(tab, aes128_extended_key);
			*(message + 4*m) = tab[0];
			*(message + 4*m + 1) = tab[1];
			*(message + 4*m + 2) = tab[2];
			*(message + 4*m + 3) = tab[3];
		}
	}


}








