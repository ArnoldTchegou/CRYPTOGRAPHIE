#include "rng.h"

void prng(uint32_t a, uint32_t b, uint32_t m) {
    seed = ((a * seed) + b ) % m;
    FILE *fptr;
    fptr = fopen("prng.out", "a");
    if (fptr == NULL) {
        printf("Could not read file\n");
        exit(1);
    }
    fprintf(fptr, "%X\n", seed);
    fclose(fptr);
}
