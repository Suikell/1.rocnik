
/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**    
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"

int solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void untilLeftPar( Stack *stack, char *postfixExpression, unsigned *postfixExpressionLength ) {

    char top;

    // Odebírej z vrcholu položky a dávej je na konec výstupního řetězce, až narazíš na levou závorku.
    // -> Tím je pár závorek zpracován
    while (1) {
        // Ziskani polozky z vrcholu zasobniku
        Stack_Top(stack, &top);
        // Odebrani
        Stack_Pop(stack);
        if (top == '(') {
            return;
        }
        // Vlozeni na konec vystupniho retezce
        postfixExpression[*postfixExpressionLength] = top;
        (*postfixExpressionLength)++;
    }
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation( Stack *stack, char c, char *postfixExpression, unsigned *postfixExpressionLength ) {


    // Pak ho na vrchol zásobníku vlož v případě, že:
    // zásobník je prázdný
    if (Stack_IsEmpty(stack)) {
        Stack_Push(stack, c);
        return;
    }
    char top;
    Stack_Top(stack, &top);
    // na vrcholu zásobníku je levá závorka
    if (top == '(') {
        Stack_Push(stack, c);
        return;
    }
    // na vrcholu zásobníku je operátor s nižší prioritou
    if ((top == '+' || top == '-') && (c == '*' || c == '/')) {
        Stack_Push(stack, c);
    //Je-li na vrcholu zásobníku operátor s vyšší nebo shodnou prioritou
    } else {
        // odstraň ho
        Stack_Pop(stack);
        // vlož ho na konec výstupního řetězce
        postfixExpression[(*postfixExpressionLength)++] = top;
        // opakuj krok 4
        doOperation(stack, c, postfixExpression, postfixExpressionLength);
    }
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
 * řetězce konstantu NULL.
 *
 * @param infixExpression Znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns Znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix( const char *infixExpression ) {

    char *postfixExpression = (char *) malloc(MAX_LEN * sizeof(char));
    if (postfixExpression == NULL || infixExpression == NULL) {
        return NULL;
    }
    Stack stack;
    Stack_Init(&stack);

    // Operator -> + - * /
    // Operand  0..9, a..z, A..Z
    unsigned int j = 0;
    for (unsigned int i = 0; infixExpression[i] != '\0'; i++ ) {

        //2. Je-li zpracovávanou položkou operand, přidej ho na konec vznikajícího výstupního řetězce.
        if ((infixExpression[i] >= '0' && infixExpression[i] <= '9') || (infixExpression[i] >= 'a' && infixExpression[i] <= 'z') || (infixExpression[i] >= 'A' && infixExpression[i] <= 'Z') ) {
            postfixExpression[j++] = infixExpression[i];
        }
        // Je-li zpracovávanou položkou levá závorka, vlož ji na vrchol zásobníku.
        else if (infixExpression[i] == '(') {
            Stack_Push(&stack, infixExpression[i]);
        // Je-li zpracovávanou položkou pravá závorka, viz untilLeftPar
        } else if (infixExpression[i] == ')') {
            untilLeftPar(&stack, postfixExpression, &j);
        // Je-li zpracovávanou položkou omezovač =, pak

        } else if (infixExpression[i] == '=') {
            while (!Stack_IsEmpty(&stack)) {
                //postupně odstraňuj prvky z vrcholu zásobníku a
                //přidávej je na konec řetězce, až zásobník zcela
                char help;
                Stack_Top(&stack, &help);
                Stack_Pop(&stack);
                postfixExpression[j++] = help;
            }
            //vyprázdníš, a na konec přidej rovnítko.
            postfixExpression[j++] = '=';
            break;
        // Je-li zpracovávanou položkou operátor, viz doOperation
        } else {
            // Operatory
            doOperation(&stack, infixExpression[i], postfixExpression, &j);
        }

    }
    postfixExpression[j++] = '\0';
    return postfixExpression;
}

/* Konec c204.c */
