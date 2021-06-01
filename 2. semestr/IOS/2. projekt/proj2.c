//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		IOS – projekt 2 (synchronizace)
//
// $NoKeywords: $IOS_proj2 $proj2.c
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-05-01
//============================================================================//
/**
 * @file	proj2.c
 * @author	Iveta Snášelová
 *
 * @brief	Implemetace 2. projektu, práce se semafory a sdílenou pamětí.
 */

#include "proj2.h" //Všechny potřebné hlavičky + makra + definice funkcí

/**
 *  Funkce ověření správnosti argumentů
 *
 * @param argc  Počet argumentů
 * @param argv  Samotné argumenty
 * @param num   Struktura pro uložení argumentů
*/
void Parse_arguments(int argc, char **argv, stdin_numbers_t *num)
{
    if(argc != 5) // 4 parametry + cesta
        goto exit;

    char *format_check = NULL;

    for(int i = 1; i < argc; i++)
    {
        int number = strtol(argv[i], &format_check, 10);    // kontrola, jestli parametr je číslo

        if(*format_check || number < 0)
            goto exit;
        else
        {
            switch (i)
            {
                case 1: if(number <= 0 || number >= 1000) goto exit;
                    else num->elf_num = (unsigned short)number;
                    break;
                case 2: if(number <= 0 || number >= 20) goto exit;
                    else num->reindeer_num = (unsigned short)number;
                    break;
                case 3: if(number > 1000) goto exit;
                    else num->elf_work = (unsigned short)number;
                    break;
                case 4: if(number > 1000) goto exit;
                    else num->reindeer_work = (unsigned short)number;
                    break;
            }
        }
    }
    return;

    exit: //chybový stav
    fprintf(stderr, "Byly zadány nesprávné argumenty!\n");
    exit(1);
} // Konec ParseArguments()

/**
 *  Funkce pro vytvoření sdílených proměnných a semaforů
 *
 *  @return Vrací chybový kód
*/
int init()
{
    MAP(reindeer_holiday);
    MAP(elves_waiting);
    MAP(task_num);
    MAP(christmas);

    if((santa_help = sem_open(SANTA_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;
    if((reindeer = sem_open(REINDEER_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;
    if((elf_help_done = sem_open(ELF_HELP_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;
    if((elf_wait = sem_open(ELF_WAIT_N, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED)
        return 1;
    if((mutex = sem_open(MUTEX_N, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED)
        return 1;
    if((start = sem_open(START_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;
    if((end = sem_open(END_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;
    if((workshop = sem_open(WORKSHOP_N, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
        return 1;

    return 0;
} //Konec init()

/**
 *  Funkce pro uklizení sdílených proměnných a semaforů
*/
void clean()
{
    UNMAP(reindeer_holiday);
    UNMAP(elves_waiting);
    UNMAP(task_num);
    UNMAP(christmas);

    sem_close(santa_help);
    sem_close(reindeer);
    sem_close(elf_help_done);
    sem_close(elf_wait);
    sem_close(mutex);
    sem_close(start);
    sem_close(end);
    sem_close(workshop);

    sem_unlink(SANTA_N);
    sem_unlink(REINDEER_N);
    sem_unlink(ELF_HELP_N);
    sem_unlink(ELF_WAIT_N);
    sem_unlink(MUTEX_N);
    sem_unlink(START_N);
    sem_unlink(END_N);
    sem_unlink(WORKSHOP_N);
}

/**
 *  Funkce pro obstarání santových povinností
 *
 * @param output    Soubor, kam zapisovat výsledek
 * @param num       Argumenty
*/
void santa(FILE *output, stdin_numbers_t *num)
{
    //Začátek santy
    sem_wait(mutex);
    fprintf(output, "%d: Santa: going to sleep\n", (*task_num)++);
    fflush(output);
    sem_post(mutex);

    while(1)
    {   // 3 elfové čekají před dílnou
        if((*elves_waiting) == 3) {
            sem_wait(santa_help);
            sem_wait(mutex);
            // Santa pomůže elfům
            fprintf(output,"%d: Santa: helping elves\n", (*task_num)++);
            fflush(output);
            // Elfové dostanou pomoc
            sem_post(mutex);
            sem_post(elf_help_done);

            // Santa jde zase spát
            sem_wait(santa_help);
            sem_wait(mutex);
            fprintf(output,"%d: Santa: going to sleep\n", (*task_num)++);
            fflush(output);
            sem_post(elf_wait);
            sem_post(mutex);
        }
        // Všichni sobi se vrátili z dovolené
        if(num->reindeer_num == (*reindeer_holiday))
        {
            // Santa zavře dílnu
            sem_wait(reindeer);
            sem_wait(mutex);
            fprintf(output,"%d: Santa: closing workshop\n", (*task_num)++);
            fflush(output);
            // Dá vědět, že skřítci můžou jít na dovolenou => "nápis na dílně Vánoce - zavřeno"
            (*christmas) = true;
            sem_post(elf_help_done);
            sem_post(workshop);
            sem_post(mutex);

            // Santa zapřáhnul soby a jede rozdávat dárky => Vánoce
            sem_wait(end);
            sem_wait(mutex);
            fprintf(output,"%d: Santa: Christmas started\n", (*task_num)++);
            fflush(output);
            sem_post(mutex);
            return;
        }
    }
} // Konec santa()

/**
 *  Funkce pro obstarání elfových povinností
 *
 * @param output    Soubor, kam zapisovat výsledek
 * @param i         ID elfa
 * @param num       Argumenty
*/
void elf(FILE *output, int i, stdin_numbers_t *num)
{
    // Začátek elfa
    sem_wait(mutex);
    fprintf(output,"%d: Elf %d: started\n", (*task_num)++, i);
    fflush(output);
    sem_post(mutex);

    srand(getpid() * time(NULL));
    while(1)
    {
        // Náhodné generování, kdy elf pracuje
        int sleep = 1000*((rand() % (num->elf_work + 1)));
        usleep(sleep);

        // Elf po své práci potřebuje pomoc, tak se zařadí před santovu dílnu
        sem_wait(elf_wait);
        sem_wait(mutex);
        fprintf(output,"%d: Elf %d: need help\n", (*task_num)++, i);
        fflush(output);
        (*elves_waiting)++;

        // Čekají tři elfové => poslední vzbudí santu
        if ((*elves_waiting) == 3) {
            sem_post(santa_help);
        } else
            sem_post(elf_wait);
        sem_post(mutex);

        // Začaly Vánoce, elf už nečeká, ale jde na dovolenou
        if((*christmas) == true) {
            goto end;
        }

        sem_wait(elf_help_done);
        sem_wait(mutex);

        // Začaly Vánoce, elf už nečeká, ale jde na dovolenou
        if((*christmas) == true) {
            sem_post(mutex);
            goto end;
        }
        // Santa pomohl elfovi
        fprintf(output,"%d: Elf %d: get help\n", (*task_num)++, i);
        fflush(output);
        (*elves_waiting)--;

        // Všichni 3 elfové dostali pomoc
        if ((*elves_waiting) == 0) {
            sem_post(santa_help);
        } else
            sem_post(elf_help_done);
        sem_post(mutex);
    }

    // Sobové se vrátili z dovolené a santa zavřel dílnu => elfové jdou na dovolenou
    end:
    sem_wait(mutex);
    fprintf(output,"%d: Elf %d: taking holidays\n", (*task_num)++, i);
    fflush(output);
    sem_post(elf_wait);
    sem_post(elf_help_done);
    sem_post(mutex);
    sem_post(start);
} // Konec elf()

/**
 *  Funkce pro obstarání povinností sobů
 *
 * @param output    Soubor, kam zapisovat výsledek
 * @param i         ID elfa
 * @param num       Argumenty
*/
void reindeer_f(FILE *output, int i, stdin_numbers_t *num)
{
    // Start soba
    sem_wait(mutex);
    fprintf(output,"%d: RD %d: rstarted\n", (*task_num)++, i);
    fflush(output);
    sem_post(mutex);

    // Random doba, kdy je sob na dovolené
    srand(getpid() * time(NULL));
    int zk = 1000*((rand() % (num->reindeer_work/2+1) - num->reindeer_work/2) + num->reindeer_work/2);
    usleep((useconds_t)(zk));

    // Sob se vrátil z dovolené
    sem_wait(mutex);
    fprintf(output,"%d: RD %d: return home\n", (*task_num)++, i);
    fflush(output);
    (*reindeer_holiday)++;
    // Všichni se vrátili z dovolené => poslední jde vzbudit santu
    if(num->reindeer_num == (*reindeer_holiday)) {
        sem_post(reindeer);
    }
    sem_post(mutex);

    sem_wait(start);
    sem_wait(mutex);
    // Santa zapřáhnul soba
    fprintf(output,"%d: RD %d: get hitched\n", (*task_num)++, i);
    fflush(output);
    // Všichni jsou připraveni k odletu
    if((*reindeer_holiday) == 1)
        sem_post(end);
    (*reindeer_holiday)--;
    sem_post(mutex);
    sem_post(start);
} // Konec reindeer_f()

int main(int argc, char **argv)
{
    stdin_numbers_t nums;   // Struktura pro argumenty
    Parse_arguments(argc, argv, &nums); // Kontrola argumentů

    // Otevření souborů pro zápis
    FILE *output;
    if((output = fopen("proj2.out", "w+")) == NULL) {
        fprintf(stderr, "Nepodařilo se otevřít soubor.\n");
        return 1;
    }
    int err_code = init();  // Vytvoření semaforů a sdílených proměnných
    if(err_code == 1)       // Kontrola chyby
        goto chyba;

    // Inicializace sdílených proměnných
    (*elves_waiting) = 0;
    (*reindeer_holiday) = 0;
    (*task_num) = 1;
    (*christmas) = false;
    // Vytvoření procesu santa
    pid_t santa_id = fork();
    if(santa_id < 0)    // Kontrola chyby
        goto chyba;
    else if(santa_id == 0)  // Proces santy
    {
        santa(output, &nums);
        return 0;
    }
    else    // Hlavní proces
    {
        for(int i = 0; i < nums.elf_num; i++)   // Generátor procesů skřítků
        {
            pid_t elf_id = fork();  // Vytvoření procesu skřítka
            if(elf_id < 0)      // Kontrola chyby
                goto chyba;
            else if(elf_id == 0)    // Proces skřítka
            {
                elf(output, i+1, &nums);
                return 0;
            }
        }
        for(int i = 0; i < nums.reindeer_num; i++)  // Vytvoření procesů sobů
        {
            pid_t reindeer_id = fork(); // Vytvoření procesu soba
            if(reindeer_id < 0)     // Kontrola chyby
                goto chyba;
            else if(reindeer_id == 0)   // Proces soba
            {
                reindeer_f(output, i+1, &nums);
                return 0;
            }
        }
    }
    // Hlavní proces čeká na všechny děti (santu, soby a skřítky)
    while (wait(NULL) > 0);
    clean();    // Uklizení semaforů a sdílených proměnných
    fclose(output); // Zavření souboru
    return 0;   // Vše proběhlo v pořádku -> vrací 0

    // Někde v průběhu programu nastala chyba => vše po sobě uklidí a vrátí 1
    chyba:
        clean();
        fclose(output);
        return 1;
}
/*** Konec souboru proj2.c ***/