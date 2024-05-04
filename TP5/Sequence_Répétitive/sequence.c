#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


uint32_t prng(uint32_t seed, uint32_t a, uint32_t b, uint32_t n) {
    return (a * seed + b) % n;
}

void Recherchemotif(uint32_t *nums, int length) {
    int maxCount = 0;
    int startIndex = -1;
    int maxPatternLength = 0;
    
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            int count = 0;
            for (int k = i,l = j; k < length && l < length; k++, l++) {
                if (nums[k] != nums[l]) {
                    break;
                }
                count++;
            }
            if (count > maxCount) {
                maxCount = count;
                startIndex = i;
                maxPatternLength = j - i;
            }
        }
    }
    
    printf("Le motif le plus répété est : ");
    for (int i = 0; i < maxPatternLength; i++) {
        printf("%X au bout de %d appels", nums[startIndex + i], startIndex + i);
    }
    printf("\n");
}

void print_tab(uint32_t tab[50], int j){
	printf("{");
	for(int i=0; i<j-1; i++){
		printf("%d, ", tab[i]);
	}
	printf("%d}\n", tab[j-1]);
}

int main() {
	int x;
    uint32_t tab[50];
    for(int i=0;i<50;i++){
        x = prng(25, 16, 256, 50);
        tab[i]=x;
    }
    print_tab(tab, 50);
    Recherchemotif(tab,50);
}
