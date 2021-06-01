/*
 * htab_init.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_init, která vytvoří prázdnou tabulku
 *
 */

#include "htab_struct.h"
#include <stdio.h>
#include <stdlib.h>

htab_t *htab_init(size_t n) {
    htab_t *tab = NULL;
    tab = (htab_t *) malloc(sizeof(htab_t) + (n * sizeof(struct htab_item)));   // Alokace tabulky
    if (tab == NULL)
        return NULL;

    tab->arr_size = n;              // Počet připravených seznamů v tabulce
    tab->size = 0;                  // Počet záznamů tabulky (je prázdná, tedy 0)

    for (size_t i = 0; i < n; i++)
        tab->ptr[i] = NULL;         // Nastavení seznamů na prázdné

    return tab;
}