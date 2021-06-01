/*
 * htab_erase.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_erase, která ruší záznam se zadaným klíčem
 *
 */

#include "htab_struct.h"
#include <stdlib.h>
#include <stdbool.h>

bool htab_erase(htab_t * t, htab_key_t key)
{
    if(t == NULL)
        return false;

    size_t index = (htab_hash_function(key) % t->arr_size);     // Zjištění v kterém seznamu tabulky se klíč může nacházet
    if(htab_find(t,key) == NULL)                                // Zjištění, zda tabulka klíč obsahuje
        return false;
    else
    {
        struct htab_item *current = t->ptr[index];              // Pomocný záznam (v něm jsou případně i odkazy na další)
        if(!strcmp(current->htab_data->key, key)) {             // Případ, kdy je záznam na začátku seznamu
            t->ptr[index] = current->next;
            t->size--;
            free((char*)current->htab_data->key);
            free(current->htab_data);
            free(current);
            return true;
        }
        while(current->next != NULL) {                           // Případ, kdy se záznam nachází někde v seznamu
            if (!strcmp(current->next->htab_data->key, key)) {
                struct htab_item *tmp = t->ptr[index]->next;
                if (current->next->next != NULL)                 // Záznam je někde uprostřed
                    current->next = current->next->next;
                else                                             // Záznam je poslední v seznamu => odkaz na další = NULL
                    current->next = NULL;
                free((char*)tmp->htab_data->key);
                free(tmp->htab_data);
                free(tmp);

                t->arr_size--;
                return true;
            }
            current = current->next;                             // Přechod na další záznam
        }
    }
    return false;
}