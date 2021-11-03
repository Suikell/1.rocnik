/*
 * htab_lookup_add.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_lookup_add, která vyhledá záznam s klíčem, případně při nenalezení ho vytvoří a vrátí ukazatel na něj
 *
 */

#include "htab_struct.h"
#include <stdlib.h>

// Funkce pro vložení záznamu
htab_pair_t * ptr_add(htab_t *t, htab_key_t key, size_t index, struct htab_item *next) {

    struct htab_item *new = malloc(sizeof(struct htab_item));
    if (new == NULL)
        return NULL;
    htab_pair_t *pair_help = malloc(sizeof(htab_pair_t));
    if (pair_help == NULL)
       return NULL;
    size_t key_size = sizeof(char) * strlen(key) +1;    // Velikost znaku * počet znaků ve slově + 1 na konečnou '\0'
    char *key_help = calloc(1,key_size);
    if (key_help == NULL)
        return NULL;

    // Přiřazení hodnot
    strcpy(key_help, key);
    new->next = next;                   // Využití parametru next (pokud je záznam poslední nastaví se na NULL, pokud ne, přiřadí se mu další záznam v seznamu)
    new->htab_data = pair_help;
    new->htab_data->key = key_help;
    new->htab_data->value = 0;
    t->ptr[index] = new;
    t->size++;
    return new->htab_data;
}
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    size_t index = (htab_hash_function(key) % t->arr_size);

    if (t->ptr[index] == NULL) {
        return ptr_add(t, key, index, NULL);                // Záznam je v seznamu jediný
    } else {
        htab_pair_t *help_find = htab_find(t, key);
        if (help_find != NULL)
            return help_find;
        else
            return ptr_add(t, key, index, t->ptr[index]);        // Záznam v seznamu není ikdyž tam nějaké záznamy již jsou => přidá se na začátek
    }
}

