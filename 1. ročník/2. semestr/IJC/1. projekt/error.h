/*
 * error.h
 * Řešení IJC-DU1, příklad b), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Deklarace funkcí pro ošetřování chyb
 */

#ifndef error_h
#define error_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
