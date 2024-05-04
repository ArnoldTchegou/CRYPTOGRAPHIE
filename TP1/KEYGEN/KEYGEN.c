//ce fichier peut etre compiler à l'aide du makefile
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

int keygen(int key_len) {
    int key, result, nombre;
    int random_fd = open("/dev/random", O_RDONLY);
    if (random_fd == -1) {
        perror("Erreur lors de l'ouverture de /dev/random");
        exit(EXIT_FAILURE);
    }

    int bytes_read = read(random_fd, &key, sizeof(key));
    if (bytes_read == -1) {
        perror("Erreur lors de la lecture de /dev/random");
        exit(EXIT_FAILURE);
    }

    close(random_fd);
    
    nombre = puissance(key_len);
    result = key&nombre;
    return result;
}

int main(int argc, char **argv) {
    if (argc!=2){
    	printf("Error!!! usage: ./KEYGEN key_len\n");
    	exit(EXIT_FAILURE);
    }
    if (atoi(argv[1])<=0){
    	printf("Error!!! invalid argument: key_len>0\n");
    	exit(EXIT_FAILURE);
    }
    // Afficher la clé générée
    printf("Cle generee : %d pour key_len = %d\n", keygen(atoi(argv[1])), atoi(argv[1]));

}
