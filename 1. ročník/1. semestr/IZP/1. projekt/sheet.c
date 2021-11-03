#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define maxLine 10242 //maximální velikost řádku = 10KiB = 10240 (+2 kvůli \n a \0)
#define maxCol 101   //maximální velikost buňky (+1 kvůli \0)

typedef struct	 //strutura pro příkazy na úpravu s řádky
{		
	bool irowT;
	bool arowT;
	bool drowT;
	bool drowsT;
	bool rowsT;
	bool beginswithT;
	bool containsT;
}paramsRows_t;

typedef struct	 //strutura pro příkazy na úpravu sloupců
{
	bool icolT;
	bool acolT;
	bool dcolT;
	bool dcolsT;
	bool csetT;
	bool toLowerT;
	bool toUpperT;
	bool roundT;
	bool intT;
	bool copyT;
	bool swapT;
	bool moveT;
}paramsCols_t;

typedef struct  //struktura pro všechny hodnoty různých příkazů
{
	int irowValue;
	int drowValue;
	int drowsValueOne;
	int drowsValueTwo; 
	int rowsValueOne;
	int rowsValueTwo;
	int beginswithValue;
	char beginswithStr[maxCol];
	int containsValue;
	char containsStr[maxCol];
	int icolValue;
	int dcolValue;
	int dcolsValueOne;
	int dcolsValueTwo;
	int csetValue;
	char csetStr[maxCol];
	int toLowerValue;
	int toUpperValue;
	int roundValue;
	int intValue;
	int copyValueOne;
	int copyValueTwo;
	int swapValueOne;
	int swapValueTwo;
	int moveValueOne;
	int moveValueTwo;

}values_t;

typedef struct  //aby funkce neměli příliš mnoho parametrů, také struktura s nejčasteji předávanými proměnnými
{
	char line[maxLine];
	char word[maxCol];
	int colNum;
	int lineNum;
	int argc; 
	char **argv;
	char delim[2]; //při první inicializace nastavím delim na mezeru ' '
	
}mainVariables_t;

//Deklarace všech funkcí používaných v programu
void irow(int* min);
void arow(int* lineNum);
void drow(char line[], int* min);
void drows(char line[], int* min);
void icol(mainVariables_t *v, int *j);
void acol(mainVariables_t *var, int j);
void dcol(char word[], int *min);
void dcols(char word[], int *min);
void toLower(char letter[]);
void toUpper(char letter[]);
void roundC(mainVariables_t *v);
void cset(mainVariables_t *v, char str[]);
void intC(mainVariables_t *v);
void copy(mainVariables_t *var, values_t *v);
void swap(mainVariables_t *var, values_t *v);
void move(mainVariables_t *var, values_t *v);
void rows(mainVariables_t *var, values_t *v, paramsCols_t *p);
void beginswith(mainVariables_t *var, values_t *v, paramsCols_t *p);
void contains(mainVariables_t *var, values_t *v, paramsCols_t *p);
void printi(char line[]);
int delimF(mainVariables_t *var);
void split(mainVariables_t *var, values_t *values, paramsCols_t *params);
int load(mainVariables_t *var, paramsRows_t *params, values_t *values, paramsCols_t *p);
int parseParamsRows(int argc, char *argv[], paramsRows_t *params, values_t *values);
int parseParamsCols(int argc, char *argv[], paramsCols_t *params, values_t *values);
int stdinCheck(int rows, int cols);

int main(int argc, char **argv)
{
	//deklarace a inicializace struktur
	paramsRows_t params = {false, false, false, false, false, false, false};
	paramsCols_t pCols = {false, false, false, false, false, false, false, false, false, false, false, false};
	values_t values;  //není třeba hned inicializovat, protože k hodnotám nikdy nepřistupuju 
	mainVariables_t var = {{'\0'}, {'\0'}, 1, 1, argc, argv, {' '}};
	
	//Před jakoukoli úpravou tabulky musím zjistit, zda na vstupu nejsou invalidní data, proto jsou obě funkce int a vrací číslo
	int returnValueRows = parseParamsRows(argc, argv, &params, &values);
	int returnValueCols = parseParamsCols(argc, argv, &pCols, &values);
	
	/*Kvůli různým chybovým hláškám a ukončení programu podle návratové hodnoty z funkcí parseParamsRows() a parseParamsCols() 
	jsem vytvořila funkci, která mi zjistí, proč se program ukončil a nakonec vrátí 1 (chyba na vstupu) nebo 0 (na vstupu jsou data v pořádku)*/
	int returnValue = stdinCheck(returnValueRows, returnValueCols);
	
	
	//Proměnnou musím mít deklarovanou před podmínkou, jelikož by existovala pouze v podmíce a já ji potřebuji dále používat
	int anotherValue;
	
	if(!returnValue) //Pokud se returnValue = 0, může program pokračovat
		anotherValue = load(&var, &params, &values, &pCols);
		
	printf("\n");
	
	//na závěr ověřím, zda nebyla jiná vstupní data invalidní, které kontroluji až ve funkci load() - př.: velikost řádku/buňky > než omezení, prázdná vstupní tabulka, ..
	if(anotherValue) //Pokud another value se != 0
		return 1;
	else
		return returnValue; //Při splnění všech vstupních podmínek bude program vracet 0
	
}
//Kontrola vstupních dat
int stdinCheck(int rows, int cols)
{
	/* Zvolila jsem několik návratových hodnot pro rozpoznání o jakou chybu jde:
		return 0  ..  vše v pořádku
		return 1  ..  při zadání příkazu je počet řádků/sloupců < 1
		return 2  ..  při více číselných hodnot u příkazu musí být N<=M
		return 3  ..  celočíselný argument příkazu obsahuje stringovou hodnotu
		return 4  ..  k příkazů není zadán požadovaný počet argumentů
		return 5 a return 6  ..  z příkazů na selekci řádků nebo zpracování dat lze volat vždy maximálně jeden */
		
	if(rows || cols) // => !=0
	{
		if(rows == 1 || cols == 1)
			fprintf(stderr, "Value of rows or cols <1!\n");
		if(rows == 2 || cols == 2)
			fprintf(stderr, "Wrong values N>M!\n");
		if(rows == 3 || cols == 3)
			fprintf(stderr, "String in value!\n");
		if(rows == 4 || cols == 4)
			fprintf(stderr, "Not enough arguments!\n");
		if(rows == 5 || cols == 5)
			fprintf(stderr, "Too many commands for rows selection\n");
		if(rows == 6 || cols == 6)
			fprintf(stderr, "Too many commands for data processing\n");
			
		return 1;
	}
	else
		return 0;
}
//Funkce na tisk pole = printf("%s", pole); 
void printi(char line[])
{
	for(int i = 0; line[i] != '\0'; i++)
		printf("%c", line[i]);
}
//Kontrola jaké příkazy pro řádky jsou zadány + zda není na vstupu chyba
int parseParamsRows(int argc, char *argv[], paramsRows_t *params, values_t *values)
{
	bool onlyOneCommand = false; //bool pro kontrolu, že je zavolán maximálně 1 příkaz ze sekce selekce řádků
	for(int i = 1; i < argc;)
	{
		//vytvoření dvou proměnných, kde budu ukládat kontrolu, že celočíselný argument neobsahuje string
		char*tmp; 
		char*tmp2;
		
		//Pokud se argv[i] = "irow => strcmp vrací 0, ale protože pokud by byl if(0), tak je podmínka nesplěna a tak musím před příkaz dát '!'
		if(!strcmp(argv[i], "irow")) 
		{
			if(i+1 != argc) //ověření, že nebudu sahat na prvek argv, který neexistuje
			{
				//můžu říct, že irow je požadovaný už tady, protože pokud by byla nějaká chyba v argumentu irow, tak program vůbec nespustím
				params->irowT = true;  
				values-> irowValue = strtol(argv[i+1], &tmp, 10); //uloží celé číslo do irowValue, zvolila jsem base = 10, protože čísla budou zadána v decimální soustavě 
				
				if(*tmp) //pokud tmp != 0 => v argumentu je string, podmínka je splněná a program ukončuj
					return 3;
				if(values->irowValue<1) //číslo požadovaného řádku < 1
					return 1;
			}
			else
				return 4; //irow nemá dostatek argumentů
		}
		if(!strcmp(argv[i], "arow")) //arow nemá žádné argumenty => není třeba nic jiného kontrolovat
		{
			params->arowT = true;
		}
		if(!strcmp(argv[i], "drow")) //stejný postup jako u irow
		{
			if(i+1 != argc)
			{
				params->drowT = true;
				values-> drowValue = strtol(argv[i+1], &tmp, 10);
				
				if(*tmp)
					return 3;
				if(values->drowValue<1)
					return 1;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "drows")) 
		{
			if(i+2 < argc) //drows požaduje 2 argumenty, špatně je, pokud zadám pouze drows, ale i drows 1, proto i+2<argc
			{
				params->drowsT = true;
				values-> drowsValueOne = strtol(argv[i+1], &tmp, 10);
				values-> drowsValueTwo = strtol(argv[i+2], &tmp2, 10);
				
				if(*tmp || *tmp2) //ani první ani druhý argument nesmí obsahovat string
					return 3;
				if(values->drowsValueOne > values->drowsValueTwo) //ověření, že N<=M
					return 2;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "rows")) 
		{
			if(i+2 < argc)
			{
				params->rowsT = true;
				if(*argv[i+2] == '-' && !argv[i+2][1]) //pokud se 2. argument rows = '-' .. !argv[i+2][1] je tam aby argument nemohl být třeba "-fsa"
				{
					values->rowsValueTwo = '-';
					if(*argv[i+1] == '-' && !argv[i+1][1]) //pokud se zároveň 1. argument rows = '-'
						values->rowsValueOne = '-';
					else
						values-> rowsValueOne = strtol(argv[i+1], &tmp, 10);//pokud se 1.argument rows != '-', musím zjistit, jestli tam je číslo a uložit si ho
				}
				else
				{	//ani jeden argument != '-' => zjištění čísel
					values-> rowsValueOne = strtol(argv[i+1], &tmp, 10); 
					values-> rowsValueTwo = strtol(argv[i+2], &tmp2, 10);
				}
				//ověření stringu v argumentu a že N<=M
				if(*tmp != '\0' || *tmp2 != '\0')
					return 3;
				if(values->rowsValueOne > values->rowsValueTwo)
					return 2;
				//ověření, že nebyl zavolán jiný příkaz na selekci řádků
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "beginswith")) 
		{	
			if(i+2 < argc)
			{
				params->beginswithT = true;
				values-> beginswithValue = strtol(argv[i+1], &tmp, 10);
				strcpy(values-> beginswithStr, argv[i+2]); //beginswith má argument string, takže si ho zkopíruji do své proměnné
			
				if(*tmp)
					return 3;
				if(values->beginswithValue<1)
					return 1;
					
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "contains")) //stejné jak u beginswith
		{
			if(i+2 < argc)
			{
				params->containsT = true;
				values-> containsValue = strtol(argv[i+1], &tmp, 10);
				strcpy(values-> containsStr, argv[i+2]);
				
				if(*tmp)
					return 3;
				if(values->containsValue<1)
					return 1;
					
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		i++;
	}
	return 0; //pokud vše proběhlo v pořádku, funkce vrací 0
}
//Kontrola jaké příkazy pro sloupce jsou zadány + zda není na vstupu chyba
int parseParamsCols(int argc, char *argv[], paramsCols_t *params, values_t *values)
{
	bool onlyOneCommand = false; //bool pro kontrolu, že je zavolán maximálně 1 příkaz ze sekce selekce řádků
	for(int i = 1; i < argc;)
	{
		//vytvoření dvou proměnných, kde budu ukládat kontrolu, že celočíselný argument neobsahuje string
		char *tmp;
		char *tmp2;
		
		//Pokud se argv[i] = "icol => strcmp vrací 0, ale protože pokud by byl if(0), tak je podmínka nesplěna a tak musím před příkaz dát '!'
		if(!strcmp(argv[i], "icol"))  //stejný postup jako u irow
		{
			if(i+1 != argc) //ověření, že nebudu sahat na prvek argv, který neexistuje
			{
				//můžu říct, že icol je požadovaný už tady, protože pokud by byla nějaká chyba v argumentu irow, tak program vůbec nespustím
				params->icolT = true;
				values-> icolValue = strtol(argv[i+1], &tmp, 10); //uloží celé číslo do irowValue, zvolila jsem base = 10, protože čísla budou zadána v decimální soustavě 
				
				if(*tmp) //pokud tmp != 0 => v argumentu je string, podmínka je splněná a program ukončuj
					return 3;
				if(values->icolValue<1) //číslo požadovaného řádku < 1
					return 1;
			}
			else
				return 4; //icol nemá dostatek argumentů
		}
		if(!strcmp(argv[i], "acol")) //acol nemá žádné argumenty => není třeba nic jiného kontrolovat
		{
			params->acolT = true;
		}
		if(!strcmp(argv[i], "dcol")) //stejný postup jako u icol
		{
			if(i+1 != argc)
			{
				params->dcolT = true;
				values-> dcolValue = strtol(argv[i+1], &tmp, 10);
				
				if(*tmp)
					return 3;
				if(values->dcolValue<1)
					return 1;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "dcols")) //dcols požaduje 2 argumenty, špatně je, pokud zadám pouze drows, ale i drows 1, proto i+2<argc
		{
			if(i+2 < argc)
			{
				params->dcolsT = true;
				values-> dcolsValueOne = strtol(argv[i+1], &tmp, 10);
				values-> dcolsValueTwo = strtol(argv[i+2], &tmp2, 10);
				
				if(*tmp || *tmp2) //ani první ani druhý argument nesmí obsahovat string
					return 3;
				if(values->dcolsValueOne > values->dcolsValueTwo)
					return 2;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "cset")) 
		{
			if(i+2 < argc)
			{
				params->csetT = true;
				values-> csetValue = strtol(argv[i+1], &tmp, 10);
				strcpy(values->csetStr, argv[i+2]); //cset má argument string, takže si ho zkopíruji do své proměnné
					
				if(*tmp)
					return 3;
				if(values->csetValue<1)
					return 1;
				//ověření, že nebyl zavolán jiný příkaz na zpracování dat
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "tolower")) //stejný postup jako u icol
		{
			if(i+1 != argc)
			{
				params->toLowerT = true;
				values-> toLowerValue = strtol(argv[i+1], &tmp, 10);
				
				if(*tmp)
					return 3;
				if(values->toLowerValue<1)
					return 1;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "toupper")) //stejný postup jako u icol
		{
			if(i+1 != argc)
			{
				params->toUpperT = true;
				values-> toUpperValue = strtol(argv[i+1], &tmp, 10);
			
				if(*tmp)
					return 3;
				if(values->toUpperValue<1)
					return 1;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "round")) //stejný postup jako u icol
		{
			if(i+1 != argc)
			{
				params->roundT = true;
				values-> roundValue = strtol(argv[i+1], &tmp, 10);
			
				if(*tmp)
					return 3;
				if(values->roundValue<1)
					return 1;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "int")) //stejný postup jako u icol
		{
			if(i+1 != argc)
			{
				params->intT = true;
				values-> intValue = strtol(argv[i+1], &tmp, 10);
			
				if(*tmp)
					return 3;
				if(values->intValue<1)
					return 1;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "copy")) //stejný postup jako u dcols
		{
			if(i+2 < argc)
			{
				params->copyT = true;
				values-> copyValueOne = strtol(argv[i+1], &tmp, 10);
				values-> copyValueTwo = strtol(argv[i+2], &tmp2, 10);
				
				if(*tmp || *tmp2)
					return 3;
				if(values->copyValueOne > values->copyValueTwo)
					return 2;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "swap")) //stejný postup jako u dcols
		{
			if(i+2 < argc)
			{
				params->swapT = true;
				values-> swapValueOne = strtol(argv[i+1], &tmp, 10);
				values-> swapValueTwo = strtol(argv[i+2], &tmp2, 10);
				
				if(*tmp || *tmp2)
					return 3;
				if(values->swapValueOne > values->swapValueTwo)
						return 2;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		if(!strcmp(argv[i], "move")) //stejný postup jako u dcols
		{
			if(i+2 < argc)
			{
				params->moveT = true;
				values-> moveValueOne = strtol(argv[i+1], &tmp, 10);
				values-> moveValueTwo = strtol(argv[i+2], &tmp2, 10);
				
				if(*tmp || *tmp2)
					return 3;
				if(values->moveValueOne > values->moveValueTwo)
					return 2;
				if(onlyOneCommand == false)
					onlyOneCommand = true;
				else
					return 5;
			}
			else
				return 4;
		}
		i++;
	}
	return 0; //vše v pořádku => vracím 0
}
//Načítání řádku ze vstupu + volání funkcí na úpravu řádků
int load(mainVariables_t *var, paramsRows_t *params, values_t *values, paramsCols_t *p)
{
	//Když volám funkce na odebrání řádku, tak ho musím odebrat i finálně v počtu řádků (nemůžu to udělat za běhu v té funkci, protože bych se zacyklila) -> speciální proměnná
	int minusLine = 1; 
	if(fgets(var->line, maxLine, stdin) != NULL) //Nejprve podmínka, zda vstup není prázdný (viz else)
	{	
		do  //používám do-while, protože jinak bych hned načetla nový řádek, ale já chci provést příkazy ještě pro řádek načtený v podmínce
	 	{
	 		if(var->line[strlen(var->line) - 1] != '\n') //nejprve podmínka, že řádek není větší než maximální velikost
	 		{	
	 			fprintf(stderr, "Too long line!\n");
	 			return 1; //pokud je, opět ukončuji funkci => program
	 		}
	 			
	 		if(delimF(var) != 0) //Volám funkci delim, abych měla řádek upravený a nebyly v něm různé delimy
	 			return 1; //Pokud je nějaká chyba v načtení delimu, končím funkci => program
	 		
	 		//Ověření, zda je příkaz zavolán a jestli splňuje číslo aktuálního řádku číslo požadovaného řádku pro úpravu
			if(params->irowT && var->lineNum == values->irowValue) //(params->drowT == true)
				irow(&var->lineNum);
			if(params->drowT && var->lineNum == values->drowValue)
				drow(var->line, &minusLine);
			if(params->drowsT && var->lineNum >= values->drowsValueOne && var->lineNum <= values->drowsValueTwo)
				drows(var->line, &minusLine);
		
		
			if(var->line[0] != '\0') //je možné, že byla zavolána funkce pro smazání řádku, v takovém případě by line[0] = '\0' a s ním již pracovat nechci, proto tato podmínka
			{	//příkazy pro selekci řádků
				if(params->rowsT)
				 	rows(var, values, p);
				else if(params->beginswithT)
					beginswith(var, values, p);
				else if(params->containsT)
				 	contains(var, values, p);
				else //pokud žádný není zadán, pracuji se všemi
					split(var, values, p); //funkce pro rozdělení sloupců + práci s nimi
			}
			else
				var->lineNum++;
		
		}while(fgets(var->line, maxLine, stdin) != NULL);
	}
	else
	{	//Pokud prázdný vstup je, vypíšu chybovou hlášku a končím funkci => program
		fprintf(stderr, "Empty input!\n");
		return 1;
	}
		
	var->lineNum -= minusLine; //na závěr vypočítání kolik je vlastně řádků
	if(params->arowT) //arow volám až po všech řádcích, protože přidá řádek za poslední
	 	arow(&var->lineNum);
	 	
	return 0; //vše v pořádku => vracím 0
}
//Načítání delim z argv[] + nahrazení různých delimů
int delimF(mainVariables_t *var)
{	
	int k = 0;
	for(int i = 0; var->line[i] != '\0'; i++) //procházím všechny řádky a nahradím různorodé delimetry
	{	if(var->argc > 2) //nejprve ověření, zda je dostatek argumentů v argv
			if(strcmp(var->argv[1], "-d") == 0)  //pokud je první argument -d, můžu delimetr změnit na požadovaný
			{
				var->delim[0] = var->argv[2][0]; //delimetr bude vždy první znak z 2. argumentu argv 
			
				//nrahazení
				for(int j = 1; var->argv[2][j]; j++)
					if(var->line[i] == var->argv[2][j])
						var->line[i] = var->delim[0];
			}
		//zároveň ověření, jestli délka jedné buňky nepřekračuje maximální velikost
		if(var->line[i] != var->delim[0]) //pokud line[i] = delim => konec jedné buňky
		{	
			k++;
			if(k > maxCol)
			{
				//jestliže překročí => vypíše chybovou hlášku a ukončí program s návratovou hodnotou 1
				fprintf(stderr, "Too long column!\n");
				return 1; 
			}
		}
		else //další buňku počítám opět od 0
			k = 0;
	}
	return 0; //jinak vrací 0 a vše je v pořádku
}
//Funkce pro rozdělení sloupců, její návratový typ je void, protože není třeba, ani něco vracela, chyby mám ošetřené již předtím
void split(mainVariables_t *var, values_t *values, paramsCols_t *params)
{	
	var->lineNum++; //při každém zavolání zvyšuji počet řádků
	int minusCol = 0;
	var->colNum = 1;
	for(int i = 0; var->line[i+1] != '\0';i++) //procházím celý řádek
	{
		int j = 0;
		for(;var->line[i] != var->delim[0] && var->line[i+1] != '\0';i++,j++) //načítám si sloupec do pole word[]
		{
			var->word[j] = var->line[i];
		}
		var->word[j] = var->line[i]; //do word[] poté vložím i delim, ať je poté správný výstup
		var->word[j+1] = '\0'; //omezím pole na správnou velikost
		
		//volání funkcí na úpravu sloupců
		if(params->swapT)
			swap(var, values);
		if(params->moveT)	
			move(var, values);
		if(params->copyT)
			copy(var, values);
			
		if(params->csetT && var->colNum == values->csetValue)	
			cset(var, values->csetStr);
		if(params->icolT && var->colNum == values->icolValue)//u některých funkcí nemá cenu předávat celou strukturu, když budu potřebovat pouze 1-2 proměnné
			icol(var, &j);
		if(params->dcolT && var->colNum == values->dcolValue)
			dcol(var->word, &minusCol);
		if(params->toLowerT && var->colNum == values->toLowerValue)
			toLower(var->word);
		if(params->toUpperT && var->colNum == values->toUpperValue)
			toUpper(var->word);
		if(params->roundT && var->colNum == values->roundValue)
			roundC(var);
		if(params->intT && var->colNum == values->intValue)
			intC(var);
		if(params->dcolsT && var->colNum >= values->dcolsValueOne && var->colNum <= values->dcolsValueTwo)
			dcols(var->word, &minusCol);
		
		
		if(var->line[i] == var->delim[0]) //Pokud se znak řádku == delim, zvýším počet sloupců
			var->colNum++;
		
		if(params->acolT && var->line[i+1] == '\0') //acol volám až na konci řádku
			acol(var, j);
		printi(var->word); //tisknu tabulku postupně po sloupcích
		
	}
	var->colNum -= minusCol; //výpočet skutečného počtu sloupců v řádku
}
//irow R - vloží řádek tabulky před řádek R > 0 (insert-row).
void irow(int* min)
{
	printf("\n");	 //protože u různých příkazů se pracuje s původní tabulkou, můžu si dovolit prostě vložit prázdný řádek
	(*min)++;       //zvýšení počtu řádků
}
//arow - přidá nový řádek tabulky na konec tabulky (append-row).
void arow(int* lineNum)
{
	printf("\n");   //protože u různých příkazů se pracuje s původní tabulkou, můžu si dovolit prostě vložit prázdný řádek
	(*lineNum)++;	//zvýšení počtu řádků
}
//drow R - odstraní řádek číslo R > 0 (delete-row).
void drow(char line[], int* min)
{
	line[0] = '\0';  //pokud první znak řádku nastavím na '\0', ostatní znaky se už dál načítat nebudou => nemusím celý řádek přepisovat
	(*min)++;	 //zvýšení počtu řádků
}
//drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N
void drows(char line[], int* min)
{
	line[0] = '\0';   //stejné jako u drow akorát volám při více řádků
	(*min)++;
}
//icol C - vloží prázdný sloupec před sloupec daný číslem C.
void icol(mainVariables_t *v, int *j)
{
	v->word[(*j)+1] = v->delim[0]; //přidám delim jako oddělovač na prázdný sloupec
	v->word[(*j)+2] = '\0';  //další sloupec je prázdný => 0
	v->colNum++; 		 //zvýším počet sloupců
	(*j)++;		//posunu na jakém sloupci jsem
}
//acol - přidá prázdný sloupec za poslední sloupec.
void acol(mainVariables_t *v, int j)
{
	v->word[j] = v->delim[0];	
	v->word[j+1] = '\n';	//stejné jak icol, akorát nesmím zapomenout, že řádek končí '\n'
	v->word[j+2] = '\0';
	//jsem na konci řádku => není třeba zvyšovat j
	v->colNum++;		
} 
//dcol C - odstraní sloupec číslo C.
void dcol(char word[], int *min)
{
	word[0] = '\0';	//stejné jak u příkazu drow
	(*min)++;
}
//dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.
void dcols(char word[], int *min)
{
	word[0] = '\0';	//stejné jak u příkazu drows
	(*min)++;
}
//tolower C - řetězec ve sloupci C bude převeden na malá písmena.
void toLower(char letter[])
{
	int dif = 'a' - 'A'; //rozdíl o jaké číslo "posunuji" znak v ASCII tabulce pro změnu na malé/velké písmeno
	for(int i = 0; letter[i] != '\0'; i++)
	{
		if(letter[i] >= 'A' && letter[i] <= 'Z') //pokud je znak velké písmeno změním na malé
			letter[i] += dif;
	}
}
//toupper C - řetězec ve sloupce C bude převeden na velká písmena.
void toUpper(char letter[])
{
	int dif = 'a' - 'A';
	for(int i = 0; letter[i] != '\0'; i++)
	{
		if(letter[i] >= 'a' && letter[i] <= 'z') //pokud je znak malé písmeno změním na velké
			letter[i] -= dif;
	}
}
//round C - ve sloupci C zaokrouhlí číslo na celé číslo.
void roundC(mainVariables_t *v)
{
	char *tmp;
	strtof(v->word, &tmp);	//nejpve zjistím, zda je ve sloupci pouze číslo
	if(!*tmp || *tmp == v->delim[0]) //pokud ano, tak můžu zaokrouhlit, jinak ignoruji
	{	
		for(int i = 0; v->word[i] != '\0'; i++)
		{
			if(v->word[i+1] == '.') //jakmile narazím na tečku, tak podle dalšího čísla zaokrouhlím
			{
				if(v->word[i+2] >= '5' && v->word[i+2] <= '9') //pokud je .číslo >= 5, zaoukrouhlím nahoru => ++
					v->word[i]++;
			
				v->word[i+1] = v->delim[0]; //tečku změním na delim
				v->word[i+2] = '\0';	     //vše ostatní za tečkou 'smažu' => ignoruji díky 0
			}
		}
	}
}
//int C - odstraní desetinnou část čísla ve sloupci C.
void intC(mainVariables_t *v)
{				//stejný postup jak u round, akorát nezaokrouhluji podle čísla za tečkou
	char *tmp;
	strtof(v->word, &tmp);
	if(!*tmp || *tmp == v->delim[0])
	{
		for(int i = 0; v->word[i] != '\0'; i++)
		{
			if(v->word[i] == '.')
			{
				v->word[i] = ':';
				v->word[i+1] = '\0';
			}
		}
	}
}
//cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.
void cset(mainVariables_t *v, char str[])
{
	int i = 0;
	while(str[i] != '\0')	//dokud neprojdu celý string
	{
		v->word[i] = str[i];  //přiřadím znak stringu do slova
		i++;
	}
	v->word[i] = v->delim[0];	//přidám delim na oddělení
	v->word[i+1] = '\0';		//případně, že pvůodní slovo bylo delší
}
char help[maxCol]; //globální proměnná, protože pouze ve funkci swap by mi potřebný sloupec na uložení zanikl 
//můžu si ji dovolit použít jak pro move tak i swap, protože podle zadání tyto dva příkazy nikdy nebudu volat zároveň

//copy N M - přepíše obsah buněk ve sloupci M hodnotami ze sloupce N.
void copy(mainVariables_t *var, values_t *v)
{
	if(var->colNum == v->copyValueOne)
		strcpy(help, var->word); //do help si uložím slovo, které budu kopírovat do sloupce M
	if(var->colNum == v->copyValueTwo)
	 	strcpy(var->word, help); //až budu ve správném sloupci => nahradím původní slovo pomocnou proměnnou
}
//swap N M - zamění hodnoty buněk ve sloupcích N a M.
void swap(mainVariables_t *var, values_t *v)
{	
	char str[maxCol];	//způsob stejný jako u copy, akorát po zkopírování slova z N do pomocné proměnné musím rovnout přepsat slovo ze sloupce N slovem ze sloupce M 
	int colHelp = 1;
	int j = 0;
	int k = 0;
	for(int i = 0; var->line[i+1] != '\0'; i++)
	{		
		if(colHelp == v->swapValueOne)
		{	
			help[j] = var->line[i]; 	
			j++;
		}
		if(colHelp == v->swapValueTwo)
		{
			str[k] = var->line[i];
			k++;
		}
		
		if(var->line[i] == var->delim[0])
			colHelp++;
	}
	help[j] = '\0';
	str[k] = '\0';
	
	if(var->colNum == v->swapValueOne)
		strcpy(var->word, str);
	else if(var->colNum == v->swapValueTwo)
		strcpy(var->word, help);
}
//move N M - přesune sloupec N před sloupec M.
void move(mainVariables_t *var, values_t *v)
{
	int colHelp = 1;
	char str[maxCol];
	int j = 0;
	for(int i = 0; var->line[i+1] != '\0'; i++) //procházím řádek
	{
		if(colHelp == v->moveValueOne) //pokud se sloupec == hodnotě N
		{
			str[j] = var->line[i];	//uložím si sloupec do pomocné proměnné
			j++;
		}	
		if(var->line[i] == var->delim[0]) //pokud oddělovač => zvýším sloupec
			colHelp++;	
	}
	str[j] = '\0'; //ošetřím konec pomocného stringu
	if(var->colNum == v->moveValueTwo)	
		printi(str);	//původní sloupec vytisknu na správném místě
	else if(var->colNum == v->moveValueOne)
		var->word[0] = '\0';	//původní sloupec smažu
}
/*rows N M - procesor bude zpracovávat pouze řádky N až M včetně (N <= M). N=1 znamená zpracování od prvního řádku. Pokud je místo čísla M zadán znak - (pomlčka), ta reprezentuje poslední řádek vstupního souboru. Pokud je pomlčka také místo sloupce N, myslí se tím výběr pouze posledního řádku. Pokud není tento příkaz zadán, uvažuje se implicitně o všech řádcích.*/
void rows(mainVariables_t *var, values_t *v, paramsCols_t *p)
{
	//podmínkami oštetřím jaké řádky upravovat
	if(v->rowsValueOne <= var->lineNum && v->rowsValueTwo == '-')
		split(var, v, p);
	else if(v->rowsValueOne <= var->lineNum && v->rowsValueTwo >= var->lineNum)
		split(var, v, p);
	else if(v->rowsValueOne == '-' && v->rowsValueTwo == '-')
		split(var, v, p);
	else{
		printi(var->line); //pokud řádek neupravuji, tak pouze vytisknu
		var->lineNum++;
	}
}
/*beginswith C STR - procesor bude zpracovávat pouze ty řádky, jejichž obsah buňky ve sloupci C začíná řetězcem STR.*/
void beginswith(mainVariables_t *var, values_t *v, paramsCols_t *p)
{
	int j = 0;
	int colHelp = 1;
	bool starts = true;
	
	for(int i = 0; var->line[i+1] != '\0'; i++) //projdu celý řádek
	{
		if(colHelp == v->beginswithValue)  //až narazím na správný sloupec, zkontroluji, zda začíná zadaným stringem
		{
			for(;v->beginswithStr[j] != '\0';i++,j++)
				if(v->beginswithStr[j] != var->line[i]) //pokud se nějaké písmeno nerovná, nastavím proměnnou starts na false a ukončím cyklus
				{
					starts = false;
					break;
				}
			break; //jelikož jsem zkontrolovala požadovaný sloupec, není třeba už procházet řádek dál
		}
		if(var->line[i] == var->delim[0]) //oddělovač => zvýšení počet sloupců
			colHelp++;
	}
	if(starts == true)
		split(var, v, p); //pokud platí, můžu začít upravovat
	else
		printi(var->line); //pokud ne, pouze vytisknu
}
/*contains C STR - procesor bude zpracovávat pouze ty řádky, jejichž buňky ve sloupci C obsahují řetězec STR.*/
void contains(mainVariables_t *var, values_t *v, paramsCols_t *p)
{
	int colHelp = 1;
	bool starts = false;
	
	for(int i = 0; var->line[i+1]; i++)
	{
		int j=0;
		for(;var->line[i] != var->delim[0] && var->line[i+1] != '\0';i++,j++)	//načítám si zvlášť sloupce
		{
			var->word[j] = var->line[i];
		}
		var->word[j] = var->line[i];
		var->word[j+1] = '\0';
		
		if(colHelp == v->containsValue) //pokud narazím na požadovaný sloupec
		{
			char *tmp = strstr(var->word, v->containsStr); //použiji funkci strstr(), která hledá substring ve stringu
			if(tmp)
				starts = true; //jestli je, nastavím hodnotu na true
			break; //po ověření požadovaného sloupce můžu ukončit celý cyklus
		}
		if(var->line[i] == var->delim[0])
			colHelp++;
	}
	if(starts == true)
		split(var, v, p);
	else
		printi(var->line);
}
