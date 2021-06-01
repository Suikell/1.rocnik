/*
 * primes.c
 * Řešení IJC-DU1, příklad a), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace algoritmu pro vypsání posledních 10 prvočísel z bitového pole, včetně zaznamenání potřebného času
 */

#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
#include <time.h>

#define N 200000000
#define last 10

int main(void)
{
    //Výpočet času algoritmu
    clock_t start = clock();

    //Vytvoření bitového pole a vytřídění na prvočísla pomocí funkce eratoshenes
    bitset_create(pole, N);
    Eratosthenes(pole);

    unsigned long primes[last];
    int j = 0;

    //Z důvodu vypsání posledních 10 - cyklus začíná na konci
   for(bitset_index_t i = bitset_size(pole)-1; i>0; i--)
    {
       //podmínka pro určení prvočísla
        if((bitset_getbit(pole, i)) == 0)
        {
            //ukládání pvočísel do pole
            primes[j++] = i;
            //po načtení desátého čísla - ukončení cyklu
            if(j==last)
                break;
        }
    }

   //Načítalo se odzadu, největší prvočíslo je na nejmenším prvku => vypisuje se naopak
    for(int i = 9; i >= 0; i--)
        printf("%lu\n",primes[i]);

    //Tisk potřebného času k provedení tohoto algoritmu
    fprintf(stderr, "Time=%.3g\n", ((double)(clock()-start)/CLOCKS_PER_SEC));

}
