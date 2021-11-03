/*
 * htab_hash_function.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce htab_hash_function, která vrátí hodnotu k indexu seznamu (je třeba %(arr_size) při samotném volání pro přesný výpočet)
 *
 */

#include "htab_struct.h"

// Použití hashovací funkce ze zadání
#ifndef HASHTEST

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}

//Použití mé vlastní implementace hashovací funkce
#else

// Vrací součin hodnot jednotlivých znaků z ASCII
// Po zavolání funkce s kombinací % arr_size se získá index do kterého seznamu se záznam má zařadit
size_t htab_hash_function(const char *str){
    size_t result = 1;
    for(int i = 0; str[i] != '\0'; i++)
        result *= (int)str[i];
    return result;
}
#endif