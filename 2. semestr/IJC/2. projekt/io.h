/*
 * io.h
 * Řešení IJC-DU2, příklad b), 16.4.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace hlavičkového souboru pro soubor io.c
 *
 */

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int read_word(char *s, int max, FILE *f);

#endif