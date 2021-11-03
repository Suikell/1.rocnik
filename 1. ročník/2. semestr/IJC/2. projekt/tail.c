/*
 * tail.c
 * Řešení IJC-DU2, příklad a), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace tail.c, který funguje jako systémový tail
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 511

// Definice položky seznamu
typedef struct item Item;
struct item {
    char data[MAX];
    Item *next;
};

// Definice lineárně spojového seznamu
typedef struct {
    Item *first;
    unsigned long num_of_lines;
} List;

// Vložení položky do seznamu
void list_insert(List *list, char *line)
{
    Item *tmp = malloc(sizeof(Item));   // Alokace místa
    if(tmp != NULL) {
        strcpy(tmp->data, line);        // Vložení řádku do dat
        tmp->next = list->first;        // Nastavení dalšího ukazatele
        list->first = tmp;              // Přiřazení na začátek seznamu
        list->num_of_lines++;           // Zvýšení počtu řádků
    }
}

// Tisk seznamu podle zadaného -n (případně 10 posledních řádků při nespecifikaci -n)
void print(Item *item, int current, int total)
{
    if (item != NULL && current<total) {                    // Procházení seznamz
        print(item->next, current + 1, total);      // Rekurzivní opakování funkce z důvodu tisknutí posledních x řádků
        printf("%s", item->data);                   // Tisk až při zpátečném procházení rekurze (tisknu sice poslední řádky ale od začátku)
    }
}

// Uvolnění seznamu
void freeList(List *list) {
    Item *tmp;
    while (list->first != NULL) {
        tmp = list->first;
        list->first = list->first->next;
        free(tmp);
    }
}

// Načtení řádků do seznamu ze souboru/stdinu
void read_line(char *line, FILE *fp, List *list)
{
    while ((fgets(line, MAX, fp)) != NULL) {
        if(strlen(line) == MAX-1){          // Omezení velikosti řádku
            while(fgetc(fp) != '\n'){}      // Vynechání zbytku řádku
            line[MAX-2] = '\n';             // Doplnění '\n' a '\0'
            line[MAX-1] = '\0';
            fprintf(stderr, "Slovo %s bylo zkráceno, protože je delší než max limit.\n",line);
        }
        list_insert(list, line);            // Vložení do seznamu
        memset(line, 0, MAX);           // Vynulování pomocného pole
    }
}

int main(int argc, char **argv) {
    bool plus = false;          // Pro případ, kdy -n +číslo (tiskne čísla od určitého řádku)
    List list;                  // Vytvoření seznamu
    list.first = NULL;          // Vynulování jeho prvků
    list.num_of_lines = 0;
    long int n_value = 10;      // Defaultně bez zadaného -n tiskne posledních 10 řádků
    int i = 1;
    char line[511] = {'\0'};

    // Rozdělení parametrů tailu
    while (i < argc) {
        if (!strcmp(argv[i], "-n")) {                               // Zadané -n
            if (i + 1 >= argc) {
                printf("Za -n musí být číslo!\n");
                return 1;
            }
            char *str_n;
            n_value = strtol(argv[i + 1], &str_n, 10);  // Kontrola, zda v čísle není nepovolený znak
            if (*str_n || n_value <= 0) {
                printf("Za -n musí být jedině kladné číslo, případně +číslo, písmena nebo záporná čísla nejsou povolena!\n");
                return 1;
            }
            if (strchr(argv[i + 1], '+'))             // Případ -n +číslo
                plus = true;
            i += 2;
        } else {                                            // Zadán soubor
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Soubor se nepodařilo otevřít.\n");
            } else {
                read_line(line, fp, &list);
            }
            fclose(fp);
            i++;
        }
    }

    // Soubor nebyl zadán => čte ze stdin
    if (list.first == NULL)
        read_line(line, stdin, &list);

    // Výpočet posledních n řádků v případě +číslo
    if (plus == true)
        n_value = list.num_of_lines - (n_value - 1);

    // Tisk n řádků
    print(list.first, 0, n_value);

    // Uvolnění seznamu
    freeList(&list);
}