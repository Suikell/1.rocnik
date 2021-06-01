/*
 * htab_clear.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_clear, která zruší všechny položky tabulky
 *
 */

#include "htab_struct.h"
#include <stdlib.h>

void htab_clear(htab_t * t)
{
    if (t == NULL)
        return;

    //Procházení postupně jednotlivých lineárně spojových seznamů (ptr)
    for(size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *current = t->ptr[i];         // Pomocný záznam (první, který může mít ukazatele na další)
        struct htab_item *deleted;                     // Mazaný záznam
        while (current != NULL)
        {
            deleted = current;                         // Mazaný záznam dám do pomocné proměnné
            current = current->next;                   // Do mazaného záznam si uložím další prvek (mazaný mám už uložený v deleted, je to tedy bezpečné)
            free((char*)deleted->htab_data->key);      // Uvolnění klíče záznamu
            free(deleted->htab_data);                  // Uvolnění struktury pro data záznamu
            free(deleted);                             // Uvolnění záznamu
        }
    }
    // Po provedení je počet záznamů i seznamů nulový => tabulka je prázdná
    t->arr_size = 0;
    t->size = 0;
}