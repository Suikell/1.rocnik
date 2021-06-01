//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		IOS – projekt 2 (synchronizace)
//
// $NoKeywords: $IOS_proj2 $proj2.h
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-05-01
//============================================================================//
/**
 * @file	proj2.h
 * @author	Iveta Snášelová
 *
 * @brief	Definice funkcí a proměnných použitých v 2. projektu
 */

// Prevence redefinování
#ifndef __PROJ2_H__
#define __PROJ2_H__

// Hlavičkové soubory použité v projektu
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>

// Struktura pro argumenty
typedef struct{
    unsigned short elf_num;
    unsigned short reindeer_num;
    unsigned short elf_work;
    unsigned short reindeer_work;
} stdin_numbers_t;

// Sdílené proměnné
int *reindeer_holiday;
int *elves_waiting;
int *task_num;
bool *christmas;

// Semafory
sem_t *santa_help;
sem_t *reindeer;
sem_t *elf_help_done;
sem_t *elf_wait;
sem_t *mutex;
sem_t *start;
sem_t *end;
sem_t *workshop;

#define SANTA_N "xsnase07_santa_help"
#define REINDEER_N "xsnase07_reindeer"
#define ELF_HELP_N "xsnase07_elves_helped"
#define ELF_WAIT_N "xsnase07_elf_waits"
#define MUTEX_N "xsnase07_mutex"
#define START_N "xsnase07_start"
#define END_N "xsnase07_end"
#define WORKSHOP_N "xsnase07_workshop"

// Makra pro vytvoření/uvolnění sdílených proměnných
#define MAP(pointer) (pointer) = mmap(NULL, sizeof(pointer), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0)
#define UNMAP(pointer) munmap(pointer, sizeof(pointer))

// Funkce
void Parse_arguments(int argc, char **argv, stdin_numbers_t *num);
int init();
void clean();
void santa(FILE *output, stdin_numbers_t *num);
void elf(FILE *output, int i, stdin_numbers_t *num);
void reindeer_f(FILE *output, int i, stdin_numbers_t *num);

#endif // Konec __PROJ2_H__

/*** Konec souboru proj2.h ***/