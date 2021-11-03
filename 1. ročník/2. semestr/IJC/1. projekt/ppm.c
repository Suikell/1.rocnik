/*
 * ppm.c
 * Řešení IJC-DU1, příklad b), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace funkcí pro načtení souboru .ppm
 */

#include "ppm.h"
#include "error.h"
#include <string.h>

struct ppm * ppm_read(const char * filename)
{
    //Promenné pro uchování parametrů souboru .ppm
    unsigned long xsize_help;
    unsigned long ysize_help;
    short int colors;

    FILE *pic_file = fopen(filename, "r");
    if(pic_file == NULL)
    {
        warning_msg("Nepodařilo se otevřít soubor\n");
        goto exit;
    }

    //Načtení formátu -ppm a kontrola
    int check_scanf = fscanf(pic_file, "P6 %lu %lu %hd ", &xsize_help, &ysize_help, &colors);
    int pic_size;
    if(check_scanf != 3 || colors > 255)
    {
        warning_msg("Chybný formát obrázku\n");
        goto exit;
    }
    else
    {
        pic_size = 3*xsize_help*ysize_help;
        if(pic_size > pic_limit)
        {
            warning_msg("Špatná velikost obrázku\n");
            goto exit;
        }
    }

    //alokace paměti pro .ppm
    struct ppm *pic = (struct ppm *)malloc(pic_size + sizeof(struct ppm));
    if(pic == NULL)
    {
        warning_msg("Nepovedla se alokace paměti pro obrázek\n");
        free(pic);
        goto exit;
    }

    pic->xsize = xsize_help;
    pic->ysize = ysize_help;

    //inicializace dat .ppm
    int check = fread(pic->data, 1, pic_size, pic_file);
    if(check > pic_size)
    {
        warning_msg("Nepodařilo se načíst obrázek");
        free(pic);
        goto exit;
    }

    fclose(pic_file);
    return pic;

    //využití goto exit: - opakující se kód - lepší přehlednost
    exit:
        fclose(pic_file);
        return NULL;
}

void ppm_free(struct ppm *p)
{
    free(p);
}
