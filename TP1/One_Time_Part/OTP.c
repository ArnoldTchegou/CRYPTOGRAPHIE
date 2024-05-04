//ce fichier peut etre compiler à l'aide du makefile
#include <stdio.h>
//fonction pour le calcul de 2^n-1
int puissance(int n){
	int base = 1;
	int resultat = 1;
	for(int i=1; i<n; i++){
		base *=2;
		resultat += base;
	}
	return resultat;
}

//fonction de chiffrement
int OTP_chiffrement(int m, int m_len, int k, int k_len){
	int nombre, x, k_ext, k_red;
	if(m_len == k_len){
		return m^k;
	}
	else if(m_len>k_len){
		x = m_len/k_len;
		k_ext = k;
		for(int i=1; i<=x; i++){
			k_ext = k^k_ext<<k_len;
		}
		if(k_ext>m){
			nombre = puissance(m_len);
			k_ext = k_ext&nombre;
		}
		return m^k_ext;
	}
	else{
		nombre = puissance(m_len);
		k_red = k&nombre;
		return m^k_red;
	}
}

//fonction de dechiffrement
int OTP_dechiffrement(int c, int c_len, int k, int k_len){
	int nombre, x, k_ext, k_red;
	if(c_len == k_len){
		return c^k;
	}
	else if(c_len>k_len){
		x = c_len/k_len;
		k_ext = k;
		for(int i=1; i<=x; i++){
			k_ext = k^k_ext<<k_len;
		}
		if(k_ext>c){
			nombre = puissance(c_len);
			k_ext = k_ext&nombre;
		}
		return c^k_ext;
	}
	else{
		nombre = puissance(c_len);
		k_red = k&nombre;
		return c^k_red;
	}
}

int main(){

	printf("le chiffrement de m = %d avec clé k = %d donne pour résultat c = %d\n", 69, 3, OTP_chiffrement(69, 7, 3, 2));
	printf("le dechiffrement de c = %d avec clé k = %d donne pour résultat m = %d\n", 58, 3, OTP_dechiffrement(58, 7, 3, 2));
}
