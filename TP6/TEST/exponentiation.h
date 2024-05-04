#ifndef _EXPONENTIATION_H_
#define _EXPONENTIATION_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t leaking_square_and_multiply(uint32_t m, uint32_t e);
uint32_t square_and_multiply(uint32_t m, uint32_t e);

#endif