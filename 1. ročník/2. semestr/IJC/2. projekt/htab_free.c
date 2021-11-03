/*
 * htab_free.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_free, zruší všechny položky tabulky a následně ji uvolní.
 */

#include "htab_struct.h"
#include <stdlib.h>

void htab_free(htab_t * t)
{
    htab_clear(t);      // Využití funkce htab_clear, která zruší položky
    free(t);            // Uvolnění tabulky
}