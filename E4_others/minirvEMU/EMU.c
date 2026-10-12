#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GET_BITS(v, hi, lo)  (((v) >> (lo)) & ((1u << ((hi) - (lo) + 1)) - 1))

uint32_t PC = 0;
uint32_t GPR[16] = {0b0};
uint32_t M[1u << 24] = {0b0};