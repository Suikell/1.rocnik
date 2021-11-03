/*
 * bitset.h
 * Řešení IJC-DU1, příklad a), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Makra/Inline funkce pro definování bitového pole a implementace základních operací s bitovými poli
 */

//Prevence redefinování funkcí/maker
#ifndef bitset_h
#define bitset_h

#include "error.h"
#include <assert.h>
#include <limits.h>

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define bit_num (sizeof(unsigned long)*CHAR_BIT)

// Vytvoření pole
// Velikost se vleze přesně do prvků bitového pole + 1 -> první prvek musí obsahovat velikost
// Velikost se nevleze přesně -> + 2, 1 pro rozšíření na zbylé bity, 1 pro první prvek jako velikost
#define bitset_create(jmeno_pole, velikost) \
unsigned long jmeno_pole[(velikost % bit_num == 0) ? (velikost/bit_num)+1 : (velikost/bit_num)+2] = {velikost, 0};\
static_assert((velikost>0), "Velikost pole musi byt > 0!");

//Pole alokované do paměti
//assert - kontroluje povolenou velikost pole
#define bitset_alloc(jmeno_pole, velikost)\
bitset_t jmeno_pole = (bitset_t)calloc(((velikost % bit_num == 0) ? ((velikost/bit_num)+1) : ((velikost/bit_num)+2)), sizeof(bitset_t));\
assert(velikost>0);\
(jmeno_pole == NULL) ?\
(error_exit("bitset_alloc: Chyba alokace paměti"),0) :\
(jmeno_pole[0] = velikost);

//Uvolnění pole z paměti
#define bitset_free(jmeno_pole)\
free(jmeno_pole)

//Použití maker
#ifndef USE_INLINE

       //Velikost pole je v prvním prvku pole
       #define bitset_size(jmeno_pole) jmeno_pole[0]

       //Nastavení výrazu na index
       //výraz = 1 -> posun jedničky na správný index a použití funkce OR (Ať už na původní místě byla 0 nebo 1, výsledek je požadovaná jednička)
       //výraz = 0 -> posun jedničky na správný index, invertování bitů (tedy na správném místě je 0) a použití funkce AND
       //Makro bitset_setbit nevrací hodnotu => lze použít konstrukci do-while(0)
       #define bitset_setbit(jmeno_pole, index, vyraz) do \
       {                                                  \
           if((bitset_size(jmeno_pole)+1) < (index+1))              \
                 error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (bitset_index_t)index, bitset_size(jmeno_pole)); \
           else                                           \
                (vyraz != 0) ? (jmeno_pole[index/bit_num + 1] |= (1UL << (index%bit_num))) : (jmeno_pole[index/bit_num + 1] &= ~(1UL << (index%bit_num))); \
       }while(0)

       //Získání bitu na indexu
       //Pomocí posunu požadovaného bitu na pravý kraj
       #define bitset_getbit(jmeno_pole, index) \
       (bitset_size(jmeno_pole) < index) ?\
       (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (bitset_index_t)index, bitset_size(jmeno_pole)),0) :\
       (((jmeno_pole[index/bit_num + 1] >> (index%bit_num)) & 1UL) ? 1UL : 0UL)

//Použití inline funkcí
#else
       inline unsigned long bitset_size(bitset_t jmeno_pole)
       {
              return jmeno_pole[0];
       }

       inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz)
       {
              if((bitset_size(jmeno_pole)+1) < (index+1))
                     error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, jmeno_pole[0]);
              else
                     (vyraz != 0) ? (jmeno_pole[index/bit_num + 1] |= (1UL << (index%bit_num))) : (jmeno_pole[index/bit_num + 1] &= ~(1UL << (index%bit_num)));
       }

       inline unsigned long bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
       {
              if(bitset_size(jmeno_pole) < index)
                     error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, jmeno_pole[0]);
              else
                     return (((jmeno_pole[index/bit_num + 1] >> (index%bit_num)) & 1UL) ? 1UL : 0UL);
              return 0;
       }

#endif  //Ukončení úseku pro inline funkce
#endif  //Ukončení bitset_h
