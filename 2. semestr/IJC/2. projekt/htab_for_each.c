/*
 * htab_for_each.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_for_each, která projde tabulku a pro každý záznam provede funkci z parametru
 *
 */

#include "htab_struct.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    for(size_t i = 0; i < t->arr_size; i++)         // Procházení seznamů
    {
        struct htab_item *current = t->ptr[i];      // Procházení záznamů v jednotlivém seznamu
        while(current!=NULL)
        {
            f(current->htab_data);                  // Volání dané funkce
            current=current->next;                  // Přesun na další záznam
        }
    }
}