/*
 * wordcount.c
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Přepis souboru wordcount.cc z jazyka C++ do C, využití hashovací tabulky
 *
 */

#include "htab_struct.h"
#include "io.h"

/* Pro testování tohoto programu jsem si zvolila knížku Wit, Humor, and Shakspeare od Johna Weise z doporučené internetové stránky http://www.gutenberg.org/.
 * Pomocí příkazu "awk -v NEW=0 -- '{for (i = 1; i <= NF; i++) wc[$i] += 1}; END {for (w in wc) NEW++; print NEW }' book.txt" v terminálu jsem zjistila,
 *  že zvolená kniha má 21559 unikátních slov.

 *   Na internetu jsem se dočetla že pro lepší efektivnost je dobré zvolit prvočíslo.
 *   Vyzkoušela jsem tedy několik možností a zjistila čas pomocí "time"
 *
 *          SIZE            TIME
 *          2687            0.631
 *          7919            0.611
 *          9803            0.561
 *          11743           0.588
 *          14591           0.574
 *          17387           0.553
 *          19309           0.547
 *
 *      Ačkoli pro velikost 19309 je čas nejrychlejší, zvolila jsem velikost 9803 (je rychlejší než další velikost 11743).
 *      Předejdu tak zbytečnému allokování příliš velkého místa a rozdíl času je přitom minimální.
 * */
#define SIZE 9803
#define MAX_WORD 127

// Funkce pro vytiksnutí slova a počtu výskytu
void print_it(htab_pair_t *data)
{
    printf("%s\t%d\n",data->key, data->value);
}
int main()
{
    char word[MAX_WORD] = {0,};                 // Pomocné pole pro slovo
    struct htab *tab = htab_init(SIZE);         // Vytvoření tabulky
    if(tab == NULL) {
        fprintf(stderr, "Selhala alokace paměti");
        goto exit;
    }
    struct htab_pair *tmp = NULL;                   // Pomocný prvek pro přidání nového kvůli kontrole správnosti alokace

    while(read_word(word, MAX_WORD, stdin) != EOF)  // Načtení slov
    {
        tmp = htab_lookup_add(tab, word);
        if(tmp == NULL) {
            fprintf(stderr, "Selhala alokace paměti");
            goto exit;
        }
        tmp->value++;
    }

// Test pro přesun tabulky do nové - spustí se pouze pokud je v Makefile -DMOVETEST
#ifdef MOVETEST
    struct htab *move_test = htab_move(tab->size, tab);
    htab_for_each(move_test, print_it);
    htab_free(move_test);

// Klasický průběh s původní tabulkou
#else
    htab_for_each(tab, print_it);
#endif

exit:
    htab_free(tab);
}