/*
 * htab_struct.h
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace hlavičkového souboru htab_struct, který obsahuje privátní deklaraci struktur pro tabulku
 *
 */

#ifndef HTAB_STRUCT
#define HTAB_STRUCT

#include "htab.h"
#include <stdint.h>
#include <stdio.h>

struct htab {
    size_t size;                    // Aktuální počet záznamů
    size_t arr_size;                // Velikost následujícího pole ukazatelů
    struct htab_item *ptr[];        // Pole záznamů
};

struct htab_item {
    struct htab_item *next;         // Ukazatel na další záznam
    htab_pair_t *htab_data;         // Veřejná struktura htab
};

#endif