/*
 * htab_move.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_move, která zkopíruje celou tabulku do nové a následně původní vyprázdní
 *
 */

#include "htab_struct.h"

htab_t *htab_move(size_t n, htab_t *from)
{
    (void)n;                                            // Velikost z parametru nevyužívám, je bezpečnější použít data přímo z původní tabulky
    struct htab *new_t = htab_init(from->arr_size);     // Vytvoření nové tabulky
    if(new_t == NULL)
        return NULL;

    new_t->size = from->size;
    new_t->arr_size = from->arr_size;
    for(size_t i = 0; i < from->arr_size; i++)
    {
        new_t->ptr[i] = from->ptr[i];                   // Přenastavení odkazu na seznam z původní tabulky do nové
    }
    htab_clear(from);                                   // Vyprázdnění původní tabulky pomocí funkce htab_clear
    return new_t;
}