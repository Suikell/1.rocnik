/*
 * bitset.c
 * Řešení IJC-DU1, příklad a), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Deklarace inline funkcí
 */

#include "bitset.h"

#ifdef USE_INLINE

unsigned long bitset_size(bitset_t jmeno_pole);
void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);
unsigned long bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif
