/*
 * ppm.c
 * Řešení IJC-DU1, příklad b), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Deklarace funkcí a struktury pro načtení souboru .ppm
 */

#ifndef ppm_h
#define ppm_h

#define pic_limit (8000*8000*3)

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif

/*Napište modul "ppm.c" s rozhraním "ppm.h",
ve kterém definujete typ:


a funkci:

struct ppm * ppm_read(const char * filename);
načte obsah PPM souboru do touto funkcí dynamicky
        alokované struktury. Při chybě formátu použije funkci warning_msg
a vrátí NULL.  Pozor na "memory leaks".

void ppm_free(struct ppm *p);
uvolní paměť dynamicky alokovanou v ppm_read

Můžete doplnit další funkce, ale pro DU1 to není nutné.
[Zamyslete se nad (ne)vhodností použití warning_msg() a promyslete
alternativní způsoby hlášení různých chyb.]

Můžete omezit max. velikost obrazových dat vhodným implementačním
        limitem (např 8000*8000*3).

Popis formátu PPM najdete na Internetu, implementujte pouze
        binární variantu P6 s barvami 0..255 a bez komentářů:
"P6" <ws>+
<xsizetxt> <ws>+ <ysizetxt> <ws>+
"255" <ws>
<binární data, 3*xsize*ysize bajtů RGB>
<EOF>*/
