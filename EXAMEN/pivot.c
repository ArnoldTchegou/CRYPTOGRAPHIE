#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char alpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//fonction qui retourne l'indice d'une lettre dans le tableau alphabétique
int indice(char lettre){
	for(int k = 0; k<26; k++){
		if(tolower(alpha[k]) == tolower(lettre)){
			return k;
		}
	}
	return -1;//code pour indiquer qu'un letrre est introuvable
}

//fonction étend la clé en fonction de la taille du message
char* extend_key(char* key, char* m){
	if(strlen(m)<=strlen(key)){
		return key;
	}
	int diff = strlen(m) - strlen(key);
	int new_len = strlen(key) + diff ;
	char* new_key = malloc(new_len*sizeof(char));
	for(int k = 0; k<new_len; k++){
		int i = k%strlen(key);
		new_key[k] = key[i];
	} 
	return new_key;
}

//fonction qui calcul le chiffré d'une lettre

char cipher_lettre(char key_letter, char m_letter){
	int i = indice(key_letter);
	int j = indice(m_letter);
	int k = (i + j)%26;
	return alpha[k];
}

//fonction qui déchiffre un lettre
char decipher_lettre(char key_letter, char m_cipher){
	int i = indice(key_letter);
	int j = indice(m_cipher);
	int k = (26 + j - i)%26;
	return alpha[k];
}

//chiffrement de viginére
void cipher_viginere(char* key, char* m, char* cipher){
	char* cipher_key = extend_key(key, m);
	for(int k = 0; k<strlen(m); k++){
		cipher[k] = cipher_lettre(cipher_key[k], m[k]);
	}
}

//déchiffrement de viginére
void decipher_viginere(char* key, char* m, char* cipher){
	char* cipher_key = extend_key(key, cipher);
	for(int k = 0; k<strlen(cipher); k++){
		m[k] = decipher_lettre(cipher_key[k], cipher[k]);
	}
}
//fonction qui 

int findPivot(uint32_t matrice[32], int i){
	int j = 0;
	int b = (matrice[j]>>(32-i))&1;
	while(b!=1){
		j++;
		if(j>=31){
			return j+1;
		}
		b = (matrice[j]>>(32-i))&1;
	}
	return j+1;
}

void swapLign(uint32_t matrice[32], int i, int j){
	matrice[i-1] = matrice[i-1]^matrice[j-1];
	matrice[j-1] = matrice[i-1]^matrice[j-1];
	matrice[i-1] = matrice[i-1]^matrice[j-1];
}

void pivot_Gauss(uint32_t matrice[32]){
	int i_pivot;
	for(int i=1; i<=32; i++){
		i_pivot = findPivot(matrice, i);
		//printf("%d\n", i_pivot);
		swapLign(matrice, i, i_pivot);
		for(int k=i; k<32; k++){
			matrice[k-1] ^= matrice[i-1];
		}
	}
}



void printmatrice(uint32_t matrice[32], int j){
	printf("{");
	for(int i=0; i<j-1; i++){
		printf("%d, ", matrice[i]);
	}
	printf("%d}\n", matrice[j-1]);
}

int main(){
	//uint32_t matrice[32] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0};
	//printf("%d\n", findPivot(matrice, 29));
	//printmatrice(matrice, 5);
	//swapLign(matrice, 1, 2);
	//printmatrice(matrice, 5);
	//pivot_Gauss(matrice);
	//printmatrice(matrice, 32);
	char* key = "bonjour";
	char* m = "bonjourbonjour";
	int n = strlen(m);
	char cipher[n];
	cipher_viginere(key, m, cipher);
	printf("texte chiffré: %s\n", cipher);
	
	char m_clair[n];
	decipher_viginere(key, m_clair, cipher);
	printf("texte dechiffré: %s\n", m_clair);
	
	
	
}

