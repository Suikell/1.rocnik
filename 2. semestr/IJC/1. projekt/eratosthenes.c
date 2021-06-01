/*
 * eratoshenes.c
 * Řešení IJC-DU1, příklad a), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce Eratosthenes k vytřídění prvočísel
 */

#include "eratosthenes.h"
#include "error.h"

void Eratosthenes(bitset_t pole)
{
    //p[0] a p[1] nejsou prvočísla
    bitset_setbit(pole,0,1);
    bitset_setbit(pole,1,1);

    //velikost pole mimo cyklus kvůli rychlejšímu algoritmu
    bitset_index_t size = sqrt(bitset_size(pole));

    for(bitset_index_t i = 2; i < size; i++)
    {
        if (bitset_getbit(pole, i) == 0) //i je prvočíslo
        {
            for (bitset_index_t n = 2; (n * i) < bitset_size(pole); n++)
            {
                bitset_setbit(pole, n * i, 1); //vyškrtnutí čísel, která nejsou prvočísla a nastavení na 1
            }
        }
    }
}
