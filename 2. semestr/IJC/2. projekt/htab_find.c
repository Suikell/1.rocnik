/*
 * htab_find.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_find, která vyhledá záznam podle klíče a vrátí na něj ukazatel (případně NULL, pokud záznam v tabulce není)
 *
 */

#include "htab_struct.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    if (t == NULL)
        return NULL;

    size_t index = (htab_hash_function(key) % t->arr_size);     // Zjištění v kterém seznamu záznam je

    struct htab_item *current = t->ptr[index];                  // Uložení prvního záznamu ze seznamu
    while (current != NULL) {
        if (!strcmp(current->htab_data->key, key))              // Kontrola, jestli procházený klíč záznamu == hledanému klíči
                return current->htab_data;
        current = current->next;                                // Přesun na další záznam
    }
    return NULL;
}