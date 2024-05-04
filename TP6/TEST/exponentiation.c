#include "exponentiation.h"

uint32_t multMod(uint32_t a, uint32_t b){
    return (a*b)%33529;
}

uint32_t leaking_square_and_multiply(uint32_t m, uint32_t e) {
    uint32_t acc = 1;

    FILE *fptr;
    fptr = fopen("sqr_and_mult.out", "a");
    if (fptr == NULL) {
        printf("Could not read file\n");
        exit(1);
    }
    while(e != 0) {
        if ((e & 1) != 0) {
            acc = multMod(acc, m);
            fprintf(fptr, "1");
        }
        fprintf(fptr, "0");
        m = multMod(m, m);
        e = e >> 1;
    }
    fprintf(fptr, "\n");
    fclose(fptr);
    return acc;
}

uint32_t square_and_multiply(uint32_t m, uint32_t e) {
    uint32_t acc = 1;
    while(e != 0) {
        if ((e & 1) != 0) {
            acc = multMod(acc, m);
        }
        m = multMod(m, m);
        e = e >> 1;
    }
    return acc;
}