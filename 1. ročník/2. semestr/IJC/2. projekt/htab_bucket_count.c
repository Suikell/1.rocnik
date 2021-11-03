/*
 * htab_bucket_count.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_bucket_count, který vrací počet ptr (lineárně spojových seznamů)
 *
 */

#include "htab_struct.h"

size_t htab_bucket_count(const htab_t * t)
{
    if(t == NULL)
        return 0;
    return t->arr_size;
}