/*
 * error.c
 * Řešení IJC-DU1, příklad b), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implentace funkcí pro ošetřování chyb
 */

#include "error.h"

void warning_msg(const char *fmt, ...)
{
    //Využití knihovny <stdarg.h>
    va_list ap;
    va_start(ap,fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}
void error_exit(const char *fmt, ...)
{
    //Není třeba psát celou funkci znovu - ošetření opakujícího se kódu
    warning_msg(fmt);
    exit(1);
}
