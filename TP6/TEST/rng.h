#ifndef _RNG_H_
#define _RNG_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t seed;


/**
 * @brief Update seed with the next PRNG value 
 *
 * @param a, the multiplicative coefficient of the PRNG.
 * @param b, the additive constant of the PRNG
 * @param m, the modulus of the PRNG
 */
void prng(uint32_t a, uint32_t b, uint32_t m);

#endif