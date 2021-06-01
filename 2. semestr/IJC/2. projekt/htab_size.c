/*
 * htab_size.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_size, která vrací počet záznamů tabulky
 *
 */

#include "htab_struct.h"

size_t htab_size(const htab_t * t)
{
    if(t == NULL)
        return 0;
    return t->size;
}