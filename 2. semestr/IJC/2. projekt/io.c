/*
 * io.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkce read_word, která načte jedno slovo
 *
 */

#include "io.h"

int read_word(char *s, int max, FILE *f) {

    if (f == NULL)
        return EOF;

    memset(s, 0, max);           // Vymazání původního "s" pro případ, že aktuální slovo bude kratší než minulé.
    int character;
    int counter = 0;

    while ((character = fgetc(f)) != EOF && !isspace(character)) {              // Načtítání slova po znacích dokud není konec souboru nebo bílý znak (\n, \t, ..)
        s[counter] = character;
        counter++;
        if (counter > max - 1) {                // Kontrola velikosti slova
            s[counter] = '\0';
            while(!isspace(fgetc(f)));      // Doprojítí slova nad limit -> aby byl zbytek zahozen.
            fprintf(stderr, "Slovo %s bylo zkráceno, protože je delší než max limit.\n", s);
            break;
        }
    }
    s[counter] = '\0';          // Každý 'string' je třeba zakončit nulou.

    if (character == EOF)       // Konec souboru
        return EOF;

    return counter;

}