/*
 * steg-decode.c
 * Řešení IJC-DU1, příklad b), 18.3.2020
 * Autor: Iveta Snášelová, FIT
 * Přeloženo: gcc 9.3.0
 * Popis: Implementace algoritmu pro dešifrování tajné zprávy ze souboru .ppm
 */

#include "eratosthenes.h"
#include "ppm.h"
#include "bitset.h"

int main(int argc, char *argv[])
{
    //Kontrola a načtení vstupního souboru .ppm
    if(argc != 2)
        error_exit("Zadán špatný počet argumentů\n");

    struct ppm *pic = ppm_read(argv[1]);
    if(pic == NULL)
        error_exit("Nepodařilo se nahrát obrázek\n");

    unsigned long pic_size = 3 * pic->xsize * pic->ysize;

    //Vytřídění prvočísel
    bitset_alloc(pic_bit, pic_size+'\0');
    Eratosthenes(pic_bit);

    //Vytvoření pole pro jednotlivá písmena zprávy
    // +1 je na '\0' v bitset_create automaticky
    bitset_create(message, CHAR_BIT)
    bitset_index_t index_mess = 0;

    int err_index = 0;

    for(bitset_index_t i = 23; i < pic_size; i++)
    {
        if(bitset_getbit(pic_bit, i) == 0)  //bit na indexu i je prvočíslo
        {
            //získání nějnižšího bitu LSb (0 x 1)
            bitset_index_t char_mess = pic->data[i] & 1;
            //Nastavení bitu v písmenu zprávy - postupně se vytvoří správný znak
            bitset_setbit(message, index_mess, char_mess);
            index_mess++;

            //8 bitů nastaveno -> správný znak zjištěný
            if(index_mess == CHAR_BIT)
            {
                //pokud je znak '\0' -> konec zprávy
                if(message[1] == '\0')
                {
                    printf("\n");
                    goto exit;
                }
                else
                {
                   printf("%c",(char)(message[1]));
                }
                index_mess = 0;
            }
        }
    }

    //využití exit k ošetření chyb a ukončení programu
    exit:
        free(pic_bit);
        ppm_free(pic);
        return (err_index == 0) ? 0 : (error_exit("Tajná zpráva není zakončena '\\0'"),1);

}
