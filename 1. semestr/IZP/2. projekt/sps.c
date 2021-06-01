#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

#define MAX_COMMAND 1000

typedef struct{	   //struct for cell
	int celLength; //length of each cell
	char *cell;    //content of the cell
}cell_t;

typedef struct{	   //struct for row
	cell_t *cells; //struct for each cell in table
}row_t;

typedef struct{		//struct for table
	int colNum;		//number of columns
	int rowsNum;	//number of rows
	int celLength1; //lenght of the longest cell
	char del;		//delimeter (if more delimeters => the first one (-d :, => del = ':'))
	row_t *rows;	//struct for each row in table
}tab_t;

typedef struct{  //structure for calculating values ​​in the original table
	int columns;
  	int longCol;
  	int rows;
	int cell;
	int longCell;
	char del;
}subVal_t; 

typedef struct{ //struct so I don't have to pass too many parameters
	int argc;
	char **argv;
	char del;
}arguments_t;

typedef struct{ // this structure is the same as temporary variable _
	int startCol;
	int endCol;
	int startRow;
	int endRow;
}changeSelection_t; 

typedef struct{ 	//structure for all commands
	int row;
	int col;
	bool irow;
	bool arow;
	bool drow;
	bool icol;
	bool acol;
	bool dcol;
	bool set;
	char setStr[MAX_COMMAND-3];
	bool clear;
	bool swap;
	bool sum;
	float sumNum;
	bool avg;
	float counter;
	bool count;
	bool len;
	bool def;
	bool use;
	bool inc;
}commands_t;

typedef struct{		//structure for temporary variables
	char num;
	char *temp;
	char *_0;
	char *_1;
	char *_2;
	char *_3;
	char *_4;
	char *_5;
	char *_6;
	char *_7;
	char *_8;
	char *_9;
}tempVariables_t;

void open(arguments_t *s, tab_t *t);
void read(char str[], FILE *fp);
void prepareDelim(arguments_t *a, char str[]);
void zk(char new[], char str[], arguments_t *s);
void notDelim(arguments_t *a, char str[], char new[], int *i, int *j);
void countTab(char str[], subVal_t *t);
void check(subVal_t *t);
void repair(char new[], char str[], subVal_t *s);
void alloc(tab_t *t, subVal_t *s);
void init(tab_t *t, char str[]);
char *repAlloc(char prev[], int size);
int findPosition(arguments_t *a, int *aPos);
void setCommands(int argPos, tab_t *t, changeSelection_t *s, arguments_t *a);
void allocTempVar(tempVariables_t *v);
int rangeSelection(changeSelection_t *s, tab_t *t, char str[]);
int numInRange(char str[], char helpStr[], int *i, int *j);
int find(tab_t *t, changeSelection_t *s, float checkNum, char find[]);
int alignCols(tab_t *t, changeSelection_t *s, commands_t *c);
int alignRows(tab_t *t, changeSelection_t *s, commands_t *c);
int parseCommands(commands_t *c, char str[]);
void callTempCommands(tab_t *t, changeSelection_t *s, commands_t *c, tempVariables_t *v);
int callCommands(tab_t *t, changeSelection_t *s, commands_t *c);
void endCell(char cell[], int end, int posEnd, int tabCol, char del);
void swap(tab_t *t, commands_t *c, int i, int j);
int arowIrow(tab_t *t, changeSelection_t *s, commands_t *c);
void irow(tab_t *t, changeSelection_t *s, commands_t *c);
void arow(tab_t *t, changeSelection_t *s, commands_t *c);
int acolIcol(tab_t *t,changeSelection_t *s, commands_t *c);
void acol(tab_t *t, changeSelection_t *s, commands_t *c);
void icol(tab_t *t, changeSelection_t *s, commands_t *c);
void drow(tab_t *t, changeSelection_t *s, commands_t *c);
void dcol(tab_t *t, changeSelection_t *s, commands_t *c);
void sumAvg(tab_t *t, changeSelection_t *s, commands_t *c, int i, int j);
void sum(char finalNum[], float sum);
void avg(char finalNum[], commands_t *c);
void count(tab_t *t, commands_t *c, changeSelection_t *s, int i, int j);
void clear(tab_t *t, int i, int j);
void setStr(tab_t *t, commands_t *c, int i, int j);
int len(tab_t *t, changeSelection_t *s, commands_t *c, int i, int j);
void def(tab_t *t, changeSelection_t *s, tempVariables_t *v);
void use(tab_t *t, changeSelection_t *s, char *temp);
void inc(tempVariables_t *v);
void noEmptyCol(tab_t *t);
void deleteQuotatM(tab_t *t);
void writeToFile(arguments_t *a, tab_t *t);
void freeTempVar(tempVariables_t *v);
void freeAll(tab_t *t);

//If I need to end my program earlier => error
//Because I don't use in many functions temp variables, I created two exits - myExit(), myBigExit()
void myExit(tab_t *t){
   	if(t != NULL)
		freeAll(t); //Need to free all memory before
	exit(1); // = return 1;
}
void myBigExit(tab_t *t, tempVariables_t *v){ //It repeated too often
	freeTempVar(v); //First free all temporary variables
	myExit(t);
}

int main(int argc, char **argv)
{
	tab_t t = {}; //This creates tab_t and initializes to default
	arguments_t a = {argc, argv, ' '};
	open(&a, &t); //upload table

	changeSelection_t sel = {1, 1, 1, 1}; //tab is setted on the first cell in the first row
	
	int argP; //variable for position, where are the commands
	int retValue = findPosition(&a, &argP); //finds commands position
	if(retValue == 1)
		myExit(&t); //if it didnt went well => exit program

	if(argv[argP][strlen(argv[argP])-1] == ';'){ //check if last command has ; int the end
		fprintf(stderr, "Commands can't end with ';'!\n");
		myExit(&t);
	}
	setCommands(argP, &t, &sel, &a); //choose selection range and call commands

	noEmptyCol(&t); //delete empty columns in the end of row
	deleteQuotatM(&t); //delete " "
	writeToFile(&a, &t);
 	freeAll(&t); //cant forget to free all memory again
	return 0;
}

//otevře soubor
void open(arguments_t *a, tab_t *t)
{
	FILE *fp; 
	subVal_t countHelp = {1,1,0,1,0,' '};

	if(a->argc>1)
   		fp = fopen(a->argv[a->argc-1] , "r");
   	else
   	{	
   		fprintf(stderr, "Which file do u wanna open?!\n");
   		myExit(t);
   	}
   	if(fp == NULL) 
   	{
    	fprintf(stderr, "Error opening file\n");
   		myExit(t);
   	}

	//Many of these functions are unnecessary (for example i didn't have to count all the rows/.. before alloc), 
	//but i have fully understood dynamic allocation on friday and that was too late to overwrite it all

   	fseek(fp, 0, SEEK_END); //it gets me to the end of file to find the size
    long int sizeTab = ftell(fp); // size of tab
    fseek(fp, 0, SEEK_SET);	//gets me to the beginning of file 

	//Before alloc I repair the tab to the right format
	char str[sizeTab]; 
	char new[sizeTab];
	char newFinal[sizeTab];
    	
    read(str, fp); //tab is in str[]
   	fclose(fp); //i dont need the file anymore

	prepareDelim(a, str); //sets right delimeters

	countHelp.del = a->del; //forget to do everything for different delims and found out too late
	t->del = a->del;

   	zk(new, str, a); //puts "" around delimeters in cells
   	countTab(new, &countHelp); //counts rows, cols, cells in tab
   	
   	repair(newFinal, new, &countHelp); //align tab
   	
   	alloc(t, &countHelp); //alloc enough memory for my tab
   	init(t, newFinal);	//sets values in tab
}
//Upload whole tab to my str[]
void read(char str[], FILE *fp)
{
	int character;
	int i = 0;
	for(; (character = fgetc(fp)) != EOF; i++) //until the character isn't end of file
	{
		str[i] = character;
	}
	str[i] = '\0';
}
//Rewrite delimeters to the first one (for example: -d :+ -> rewrite + on :)
void prepareDelim(arguments_t *a, char str[])
{
	if(a->argc > 2) 
	{
		if(strcmp(a->argv[1], "-d") == 0) //check if the delim was selected
		{
			for(int i = 0; str[i] != '\0'; i++)
			{
				a->del = a->argv[2][0];
				if(str[i] == '\\') //if \delim => its the part of the cell => dont rewrite
				{
					i++;
					continue;
				}
				if(str[i] == '\"')	// if "delim somwhere in str" => delim is part of the cell as well
				{
					i++;
					while(str[i] != '\"')
						i++;
					continue;
				}
				for(int j = 0; a->argv[2][j] != '\0'; j++)
				{
					if(str[i] == a->argv[2][j]) 
						str[i] = a->del;	//makes all delimeters like the first one 
				}
			}
		}
	}
}
//repair cells with delimeters
void zk(char new[], char str[], arguments_t *a)
{
  	int j = 0;
	for(int i = 0; str[i] != '\0'; i++, j++)
	{
		new[j] = str[i];
		if(str[i] == '\\') //if '\delim' => delim in cell
		{
			i++;
			notDelim(a, str, new, &i, &j); //it should be in cell => put "" around delim
		}	
		if(str[i] == '"') //if "delim" => delim in cell
		{
			i++;
			while(str[i] != '"')
			{	
				new[j] = str[i];
				notDelim(a, str, new, &i, &j); //it should be in cell => put "" around delim
				j++;
				i++;
			}
			j--;
		}
	}
	new[j] = '\0';
}

//delim in cell => put "" around
void notDelim(arguments_t *a, char str[], char new[], int *i, int *j)
{
	if(a->argc > 2 && strcmp(a->argv[1], "-d") == 0)
	{
		for(int k = 0; a->argv[2][k] != '\0'; k++)
		{
			if(str[*i] == a->argv[2][k]) //need to check, if it is the delim
			{
				new[*j] = '\"';
				new[*j+1] = a->argv[2][k];
				new[*j+2] = '\"';
				*j+=2;
				break;
			}
		}
	}
	else //if default delim
	{
		if(str[*i+1] == ' ')
		{
			(*i)++;
			new[*j] = '\"';
			new[*j+1] = str[*i];
			new[*j+2] = '\"';
			*j+=2;
		}
	}
}

//count num of cols,rows,size of cell
void countTab(char str[], subVal_t *t)
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '\n') //=> next line
		{
			check(t); //finds the longest cell
			t->rows++; 
			if(t->longCol < t->columns) //finds the right number of columns, so i can later repair every row to have same number of columns 
				t->longCol = t->columns;
			t->columns = 1; //new line => count columns from 1 again
			continue;
		}
		if(str[i] != t->del) //until character != delim => increase number of characters in cell 
		{
			t->cell++;
			if(str[i] == '\"' && str[i+1] == t->del) //check if around delim are ""
			{
				i+=1;
				t->cell++;
			}
		}
		else //char == delim => next colNum
		{
			t->columns++;
			check(t);  //finds the longest cell
		}
	}
}

//if new cell is bigger than previous => repair the size of longCell
//i use it multiple times, so it deserves to be in function
void check(subVal_t *t)
{
	if(t->longCell < t->cell)
		t->longCell = t->cell;
	t->cell = 1;
}

//sets same num of cols in every row
void repair(char new[], char str[], subVal_t *s)
{
	int help = 1; //==number of columns in every row
	int j = 0;
	for(int i = 0; str[i] != '\0'; i++, j++)
	{
		if(str[i] == s->del && str[i-1] != '\"') //first i need to count columns in every row
			help++;
			
		if(str[i] == '\n') //if new line 
		{
			if(help < s->longCol) //if columns in row < actual number of columns
			{
				while(help != s->longCol) //add more columns
				{
					new[j] = s->del;
					j++;
					help++;
				}
			}
			help = 1; //then new line => start count columns again
		}
		new[j] = str[i];
	}
	new[j] = '\0';
}

//alloc enough memory for my tab
void alloc(tab_t *t, subVal_t *s)
{
	t->rows = malloc(s->rows * sizeof(row_t)); //first alloc memory for rows
	if(t->rows == NULL){ //check if everything went well
		fprintf(stderr, "Wrong malloc!\n");
		myExit(t);
	}

	for(int i = 0; i < s->rows; i++) //in every row alloc memory for columns
	{
		t->rows[i].cells = malloc(s->longCol * sizeof(cell_t));
		if(t->rows->cells == NULL){
			fprintf(stderr, "Wrong malloc!\n");
			myExit(t);
		}
		for(int j = 0; j < s->longCol; j++) //in every column alloc memory for cell
		{
			t->rows[i].cells[j].cell = malloc(s->longCell * sizeof(char) + 2); //+2 for '\0'
			if(t->rows == NULL){
				fprintf(stderr, "Wrong malloc!\n");
				myExit(t);
			}
		}
	}
	
	//sets numbers to actual tab
	t->rowsNum = s->rows;
	t->colNum = s->longCol;
	t->celLength1 = s->longCell;
}

//initialize tab
void init(tab_t *t, char str[])
{
	int l = 0;
	int k = 0;
	for(int i = 0; i < t->rowsNum; i++) //rows
	{
		for(int j = 0; j < t->colNum; j++) //columns/cells
		{
			for(k = 0; k < t->celLength1; k++, l++) //characters in columns/cells
			{
				t->rows[i].cells[j].cell[k] = str[l];
				
				if(str[l] == '\"') //if "" => delim in cell => skip that, so it doesnt create new cell
				{
					t->rows[i].cells[j].cell[k+1] = str[l+1];
					t->rows[i].cells[j].cell[k+2] = str[l+2];
					l+=2;
					k+=2;
				}
				else if(str[l] == t->del) //check if i should move to the next column
				{	
					t->rows[i].cells[j].cell[k+1] = '\0';
					t->rows[i].cells[j].cell = repAlloc(t->rows[i].cells[j].cell, k+1); //because i alloced memory for the longest cell, now i have to resize it
					t->rows[i].cells[j].celLength = k+1;
					l++;
					break;
				}
				else if(str[l] == '\n') //check if i should move to the next row
				{	
					t->rows[i].cells[j].cell[k+1] = '\0';
					t->rows[i].cells[j].cell = repAlloc(t->rows[i].cells[j].cell, k+1); //resize cell
					t->rows[i].cells[j].celLength = k+1;
					l++;
					break; //it gets me out of the cycle for cells
				}
			}
			if(str[l-1] == '\n') //but i need to get out of the cycle for columns as well
			{
				break;
			}
		}
	}
}

//realloc size of the cell (how much each cell needs)
char *repAlloc(char prev[], int size)	//returns new realloced cell
{
	char *resized;
	resized = realloc(prev, size*sizeof(char) + 2); //+2 for '\0'
	if(resized != NULL)
		prev = resized;
	return prev;
	
}
//find position where the commands are in argv[]
int findPosition(arguments_t *a, int *aPos)
{   // it should always be > 2, beacuse the last argument is file
	if(a->argc > 2 && strcmp(a->argv[1], "-d") != 0)
		*aPos = 1;
	else if(a->argc > 4) //delimeter is chosen => more arguments ./sps -d : 'commands' tab.txt
		*aPos = 3;
	else
	{ 	fprintf(stderr, "Not enough arguments!\n");
		return 1;
	}
	return 0;
}
//divide commands and call them
void setCommands(int argPos, tab_t *t, changeSelection_t *s, arguments_t *a)
{
	char command[MAX_COMMAND];
	int j = 0;

	tempVariables_t tempV = {};
	allocTempVar(&tempV); //alloc temporary variables

	for(int i = 0; a->argv[argPos][i] != '\0'; i++, j++)
	{
		if(a->argv[argPos][i] != ';' && a->argv[argPos][i+1] != '\0') //divide commands
				command[j] = a->argv[argPos][i]; //put every command seperately to my char command[]
		else
		{
			if(a->argv[argPos][i+1] == '\0'){ //if the command is the last one, it doesnt end with ';' 
				command[j] = a->argv[argPos][i];
				command[j+1] = '\0';
			}
			else
				command[j] = '\0';
				
			commands_t com = {}; //create that structure every time, so u dont have to set it all to false again
			if(command[0] == '[') //if u want to change range selection
			{	
				int ret = rangeSelection(s,t,command); //process the command
				if(ret == 1)
					myBigExit(t, &tempV);

				if(s->endCol > t->colNum){ //if rows selection is bigger than rows in tab
					ret = alignCols(t,s,&com);
					if(ret == 1)
						myBigExit(t, &tempV);
				}
				if(s->endRow > t->rowsNum){ //same just for columns
					ret = alignRows(t,s,&com);
					if(ret == 1)
						myBigExit(t, &tempV);
				}
			}
			else
			{	
				int ret = parseCommands(&com,command); //choose which command is supposed to be made
				if(ret == 1)
					myBigExit(t, &tempV);
				
				if(com.def == true || com.inc == true || com.use){ //i have special function for temporary commands
					tempV.num = command[5] - 48; //i need the actual number, not ascii => -48 => -'0'
					callTempCommands(t,s,&com,&tempV);
				}
				ret = callCommands(t,s,&com); //now call the right command
				if(ret == 1)
					myBigExit(t, &tempV);
			}
			j = -1;				
		}
	}
	freeTempVar(&tempV); //free temporary variables
}

void allocTempVar(tempVariables_t *v)
{
	v->_0 = calloc(1,1); //i use calloc, so it sets allocated memory to zero.
	v->_1 = calloc(1,1);
	v->_2 = calloc(1,1);
	v->_3 = calloc(1,1);
	v->_4 = calloc(1,1);
	v->_5 = calloc(1,1);
	v->_6 = calloc(1,1);
	v->_7 = calloc(1,1);
	v->_8 = calloc(1,1);
	v->_9 = calloc(1,1);
}

int rangeSelection(changeSelection_t *s, tab_t *t, char str[])
{
	if(strstr(str, "[_]")) //check if range selection should be setted to default values
	{
		s->startRow = 1;
		s->endRow = 1;
		s->startCol = 1;
		s->endCol = 1;
	}
	else
	{
		char helpStr[MAX_COMMAND];
		int j = 0;
	
		if(strstr(str, ",")) //=> dont look for anything in tab, just set selection
		{
			int i = 1; 
			if(str[i] == '_') //need to separately check if its not _, because thats not a number
			{
				s->startRow = 1;
				s->endRow = t->rowsNum;
				i+=2;	
			}
			else
			{	
				s->startRow = numInRange(str, helpStr, &i, &j); //put the number to s->startRow
				if(s->startRow == INT_MAX)
					return 1;
				s->endRow = s->startRow; //if only [,] => its selected only one cell => s->endRow == s->startRow
			}
			if(str[i] == '_')
			{						//same just for columns
				s->startCol = 1;
				s->endCol = t->colNum;
				i+=2;	
			}
			else
			{	
				s->startCol = numInRange(str, helpStr, &i, &j);
				if(s->startCol == INT_MAX)
					return 1;
				s->endCol = s->startCol;
			}
			if(str[i] != '\0') //=> its not only [R,C], but [R1,C1,R2,C2]
			{	
				if(str[i] == '-' || str[i] == '_') //wasnt sure if it really should have been '-' or it was another mistake in project assignment
				{	
					s->endRow = t->rowsNum;
					i+=2;	
				}								//now i do the same as for R1,C1, just for s->endRow, s->endCol (R2,C2)
				else
				{
					s->endRow = numInRange(str, helpStr, &i, &j);
					if(s->endRow < s->startRow) //check - first value must be < than second value
					{
						fprintf(stderr, "1.row <= 2.row!\n");
						return 1;
					}
				}
				if(str[i] == '-' || str[i] == '_')
				{
					s->endCol = t->colNum;
					i+=2;	
				}
				else
				{
					s->endCol = numInRange(str, helpStr, &i, &j);
					if(s->endCol < s->startCol)
					{
						fprintf(stderr, "1.column <= 2.column!\n");
						return 1;
					}
				}
			}
		}
		//other commands with [] are min,max and find Str
		char substring[MAX_COMMAND];
		int ret;
		if(strstr(str, "min"))
		{
			ret = find(t,s,FLT_MAX,NULL); //find min in tab
			if(ret == 1)
				return 1;
		}
		else if(strstr(str, "max"))								//i use FLT_MAX and FLT_MIN to know, that some number will be 100% smaller/bigger
		{
			ret = find(t,s,FLT_MIN,NULL); //fint max in tab
			if(ret == 1)
				return 1;
		}
		else if(strstr(str, "find"))
		{
			char *zk = strstr(str, " ");
			for(int i = zk-str+1; str[i+1] != '\0'; i++,j++)
				substring[j] = str[i];
			substring[j] = '\0';
		
			ret = find(t,s,0.0,substring); //find string in tab
			if(ret == 1)
				return 1;
		}
	}
	return 0;
}

int numInRange(char str[], char helpStr[], int *i, int *j)
{
	int returnValue;
	char *tmp;

	for(; str[*i] != ',' && str[*i] != ']'; (*i)++, (*j)++)
		helpStr[*j] = str[*i];	//puts to helpStr only the number (i need to use cycle for numbers > 9)
	helpStr[*j] = '\0';
	*j=0;
	(*i)++;
	
	returnValue = strtol(helpStr, &tmp, 10); //check if it is just a number 
	if(*tmp){
		fprintf(stderr, "1: string in value\n");
		return INT_MAX; //i use INT_MAX to be sure that the error return value wont be the number of column/row
	}
	return returnValue;
}

int find(tab_t *t, changeSelection_t *s, float checkNum, char find[])
{
	bool findMIN = false;
	bool findMAX = false;
	bool findSTR = false;
	
	//first check which value im looking for
	if(checkNum == FLT_MAX)
		findMIN = true;
	else if(checkNum == FLT_MIN)
		findMAX = true;
	else
		findSTR = true;
		
	char *tmp;
	int line = 0;
	int col = 0;
	
	for(int i = (s->startRow-1); i < s->endRow; i++)
	{
		for(int j = (s->startCol-1); j < s->endCol; j++)
		{
			float try = strtof(t->rows[i].cells[j].cell, &tmp); //various numbers in table
			if(try != '\0')
			{
				if(checkNum > try && findMIN == true)
				{
					checkNum = try;
					line = i+1;
					col = j+1;
				}
				if(checkNum < try && findMAX == true)
				{
					checkNum = try;
					line = i+1;
					col = j+1;
				}
			}
			if(findSTR == true && strstr(t->rows[i].cells[j].cell, find))
			{
				line = i+1;
				col = j+1;
			}
		}
	}
	if(line && col)
	{
		s->startRow = line;
		s->endRow = line;
		s->startCol = col;
		s->endCol = col;
	}
	else{
		fprintf(stderr, "In tab is not searched value!\n");
		return 1;
	}
	return 0;
}
//if columns selection is bigger than number of columns in tab
int alignCols(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = s->endCol-t->colNum; i >= 1; i--)
	{
		s->endCol = t->colNum;
		int ret = acolIcol(t,s,c); //i use function which add columns to table
		if(ret == 1)
			return 1;
	}
	s->endCol = t->colNum;
	return 0;
}
//same just for rows
int alignRows(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = s->endRow-t->rowsNum; i >= 1; i--)
	{
		s->endRow = t->rowsNum;
		int ret = arowIrow(t,s,c); //i use function which add row to table
		if(ret == 1)
			return 1;
	}
	s->endRow = t->rowsNum;
	return 0;
}
//finds out which command is called and store the argument of the command
int parseCommands(commands_t *c, char str[])
{
	int firstNum = 0;
	int secondNum = 0;
	char helpStr[MAX_COMMAND];
	char *tmp;
	int j = 0; 
	char *zk;
	
	if((zk = strstr(str, "["))) //Finds out if command contains [] => numbers
	{	
		for(int i = zk-str+1; str[i] != '\0'; i++) //zk-str = position, where [ is 
		{
			for(;str[i] != ',';i++, j++) //puts to helpStr only the number
				helpStr[j] = str[i];
			helpStr[j] = '\0';
			j=0;
			
			firstNum = strtol(helpStr, &tmp, 10); //check if it is the number
			if(*tmp){
				fprintf(stderr, "String in value\n");
				return 1;
			}
				
			for(;str[i+1] != ']';i++, j++) //---------------------------------------------------------------------------------------------------------MAYBE numInRange()?
				helpStr[j] = str[i+1];
			helpStr[j] = '\0';
			j=0;
			
			secondNum = strtol(helpStr, &tmp, 10);
			if(*tmp){
				fprintf(stderr, "String in value\n");
				return 1;
			}
			c->row = firstNum-1; //set to command row and col
			c->col = secondNum-1;
			break;
		}
	}
	if(strstr(str, "irow"))
		c->irow = true;
	else if(strstr(str, "arow"))
		c->arow = true;
	else if(strstr(str, "drow"))
		c->drow = true;
	else if(strstr(str, "icol"))
		c->icol = true;
	else if(strstr(str, "acol"))
		c->acol = true;
	else if(strstr(str, "dcol"))
		c->dcol = true;	
	else if(strstr(str, "clear"))
		c->clear = true;	
	else if(strstr(str, "swap"))
		c->swap = true;
	else if(strstr(str, "sum"))
		c->sum = true;
	else if(strstr(str, "avg"))
		c->avg = true;
	else if(strstr(str, "count"))
		c->count = true;
	else if(strstr(str, "len"))
		c->len = true;
	else if(strstr(str, "set")) //set Str => i need to find the Str
	{	
		c->set = true;
		for(int i = 4; str[i] != '\0'; i++, j++)
			 c->setStr[j] = str[i];
	}
	else if(strstr(str, "def"))
			c->def = true;
	else if(strstr(str, "use"))
			c->use = true;
	else if(strstr(str, "inc"))
			c->inc = true;
	else{
		fprintf(stderr, "I dont recognize that command!\n");
		return 1;
	}
	return 0;
}
//call functions for commands which work with temp variables
void callTempCommands(tab_t *t, changeSelection_t *s, commands_t *c, tempVariables_t *v)
{
	switch(v->num) //first i need to upload right variable to my tmp
	{
		case 0: v->temp = v->_0; break;
		case 1: v->temp = v->_1; break;
		case 2: v->temp = v->_2; break;
		case 3: v->temp = v->_3; break;			//i use special temp variable, so i dont need to call function for every _x 
		case 4: v->temp = v->_4; break;
		case 5: v->temp = v->_5; break;
		case 6:	v->temp = v->_6; break;
		case 7: v->temp = v->_7; break;
		case 8: v->temp = v->_8; break;
		default: v->temp = v->_9;
	}
	if(c->def == true)
		def(t,s,v);
	if(c->use == true)
		use(t,s,v->temp);
	if(c->inc == true)
		inc(v);

	switch(v->num)	//then i need to return value to the right variable
	{
		case 0: v->_0 = v->temp; break;
		case 1: v->_1 = v->temp; break;
		case 2: v->_2 = v->temp; break;
		case 3: v->_3 = v->temp; break;
		case 4: v->_4 = v->temp; break;
		case 5: v->_5 = v->temp; break;
		case 6:	v->_6 = v->temp; break;
		case 7: v->_7 = v->temp; break;
		case 8: v->_8 = v->temp; break;
		default: v->_9 = v->temp;
	}
}
//call all other commands
int callCommands(tab_t *t, changeSelection_t *s, commands_t *c)
{
	int ret;
	for(int i = s->startRow-1; i < s->endRow; i++) //i need to call it for every selected cell
		for(int j = s->startCol-1; j < s->endCol; j++)
		{
			if(c->set == true)
				setStr(t,c,i,j);
			else if(c->clear == true)
				clear(t,i,j); 
			else if(c->swap == true)
				swap(t,c,i,j);
			else if(c->sum == true || c->avg == true)
				sumAvg(t,s,c,i,j);
			else if(c->count == true)
				count(t,c,s,i,j);
			else if(c->len == true){
				ret = len(t,s,c,i,j);
				if(ret == 1)
					return 1;
			}
		}
	if(c->dcol == true)
		dcol(t,s,c);
	if(c->acol == true || c->icol == true){
		ret = acolIcol(t,s,c);
		if(ret == 1)
			return 1;
	}
	if(c->drow == true)
		drow(t,s,c);
	if(c->arow == true || c->irow == true){
		ret = arowIrow(t,s,c);
		if(ret == 1)
			return 1;
	}
	return 0;
}
//I often check what should i put in the end of cell, so i created a function for it
void endCell(char cell[], int end, int posEnd, int tabCol, char del)
{
	if(end == tabCol-1) //if selected cell == last cell in row
		cell[posEnd] = '\n';
	else
		cell[posEnd] = del;
	cell[posEnd+1] = '\0';
}
//swap [R,C] - vymění obsah vybrané buňky s buňkou na řádku R a sloupci C
void swap(tab_t *t, commands_t *c, int i, int j)
{	//created temp strings for easier swap
	char str1[t->celLength1]; 
	char str2[t->celLength1];
	strcpy(str1, t->rows[i].cells[j].cell);
	strcpy(str2, t->rows[c->row].cells[c->col].cell);
	//realloc size of first cell to the size of second cell
	char *reall = realloc(t->rows[i].cells[j].cell, (strlen(str2))*sizeof(char)+2);
	if(reall != NULL)
	{		
		t->rows[i].cells[j].cell = reall;	//if realloc was successful => copy content of second cell to the first one
		strcpy(t->rows[i].cells[j].cell, str2);
		t->rows[i].cells[j].celLength = strlen(t->rows[i].cells[j].cell); //cant forget to change length of that cell
		endCell(t->rows[i].cells[j].cell, j, t->rows[i].cells[j].celLength-1, t->colNum, t->del); //check end of the cell (in case one of the cell is the last one in the row)

		reall = realloc(t->rows[c->row].cells[c->col].cell, (strlen(str1))*sizeof(char)+2);
		if(reall != NULL)
		{														//here i did the same just for the other cell
			t->rows[c->row].cells[c->col].cell = reall;
			strcpy(t->rows[c->row].cells[c->col].cell, str1);
			t->rows[c->row].cells[c->col].celLength = strlen(t->rows[c->row].cells[c->col].cell);
			endCell(t->rows[c->row].cells[c->col].cell, c->col, t->rows[c->row].cells[c->col].celLength-1, t->colNum, t->del);
		}
	}
}
//function for commands irow and arow -> because the code is almost the same for both commands
int arowIrow(tab_t *t, changeSelection_t *s, commands_t *c)
{
	row_t *reall = realloc(t->rows, (t->rowsNum+1)*sizeof(row_t)); //realloc memory for rows
	if(reall != NULL)
	{
		t->rows = reall;
		t->rows[t->rowsNum].cells = malloc(t->colNum * sizeof(cell_t)); //malloc memory for new columns
		if(t->rows[t->rowsNum].cells == NULL){
			fprintf(stderr, "Wrong malloc - arow/irow\n");
			return 1;
		}
		for(int i = 0; i < t->colNum; i++)
		{
			t->rows[t->rowsNum].cells[i].cell = malloc(sizeof(char) +2); //malloc memory for every cell
			if(t->rows[t->rowsNum].cells[i].cell == NULL){
				fprintf(stderr, "Wrong malloc - arow/irow -cell\n");
				return 1;
			}
			t->rows[t->rowsNum].cells[i].celLength = 1;
			endCell(t->rows[t->rowsNum].cells[i].cell, i, 0, t->colNum, t->del); //check end
			
		}
	}
	else{
		fprintf(stderr, "Wrong realloc - arow/irow\n");
		return 1;
	}
	if(c->irow == true)
		irow(t,s,c);		//here i call function separetaly for irow and arow to finish the differences
	if(c->arow == true)
		arow(t,s,c);
	t->rowsNum++;
	return 0;
}
//irow - vloží jeden prázdný řádek nalevo od vybraných buněk. --- PŘED
void irow(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = t->rowsNum; i >= s->startRow; i--)
	{
		for(int k = 0; k < t->colNum; k++)
		{
			c->row = i;
			c->col = k;
			swap(t, c, i-1, k); //i use swap to move all cells, so the new row is where it should be
		}
	}
}
//arow - přidá jeden prázdný řádek napravo od vybraných buněk.  --- ZA 
void arow(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = t->rowsNum; i > s->startRow; i--)
	{
		for(int k = 0; k < t->colNum; k++)
		{
			c->row = i;
			c->col = k;
			swap(t, c, i-1, k); //same
		}
	}
}
//same as irowArow, just for columns
int acolIcol(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = 0; i<t->rowsNum; i++)
	{
		cell_t *reall = realloc(t->rows[i].cells, (t->colNum+1)*sizeof(cell_t)); //realloc memory for columns
		if(reall != NULL)
		{
			t->rows[i].cells = reall;
			for(int j = t->colNum; j <= t->colNum; j++)
			{
				t->rows[i].cells[j].cell = malloc(sizeof(char)+2); //malloc memory for new cell
				if(t->rows[i].cells[j].cell == NULL){
					fprintf(stderr, "Wrong malloc - acol/icol\n");
					return 1;
				}
				else
				{
					t->rows[i].cells[j].celLength = 1;
					endCell(t->rows[i].cells[j].cell,s->endCol, 0, t->colNum+1, t->del); //end check
					if(s->endCol == t->colNum)
						t->rows[i].cells[t->colNum-1].cell[t->rows[i].cells[t->colNum-1].celLength-1] = t->del;
				}
			}
		}
		else{
			fprintf(stderr, "Wrong realloc - acol/icol\n");
			return 1;
		}	
	}
	t->colNum++;
	if(c->acol == true)
		acol(t,s,c);
	if(c->icol == true)
		icol(t,s,c);
	return 0;
}
//acol - přidá jeden prázdný sloupec napravo od vybraných buněk.
void acol(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = 0; i < t->rowsNum; i++)
	{
		for(int j = t->colNum-1; j > s->endCol; j--)
		{
			c->row = i;
			c->col = j-1;
			swap(t, c, i, j); //again swap to move cells
		}
	}
}
//icol - vloží jeden prázdný sloupec nalevo od vybraných buněk.
void icol(tab_t *t, changeSelection_t *s, commands_t *c)
{
	for(int i = 0; i < t->rowsNum; i++)
	{
		for(int j = t->colNum-1; j >= s->endCol; j--)
		{
			c->row = i;
			c->col = j-1;
			swap(t, c, i, j); //same
		}
	}
}

//drow - odstraní vybrané řádky.
void drow(tab_t *t, changeSelection_t *s, commands_t *c)
{
	int i = s->startRow - 1;
	for(int j = s->endRow; j < t->rowsNum; i++,j++)
	{
		for(int k = 0; k < t->colNum; k++)
		{
			c->row = i;
			c->col = k;
			swap(t, c, j, k); //first move rows
		}
	}
	//than delete right number of rows from the end of the table
	int numDelete = s->endRow - s->startRow + 1;
	for(int i = t->rowsNum - numDelete; i < t->rowsNum; i++)
	{
		for(int j = 0; j < t->colNum; j++)
		{
			free(t->rows[i].cells[j].cell);
			t->rows[i].cells[j].cell = NULL;
		}
		free(t->rows[i].cells);
		t->rows[i].cells = NULL;
	}
	t->rowsNum -= numDelete;
}

//dcol - odstraní vybrané sloupce.
void dcol(tab_t *t, changeSelection_t *s, commands_t *c)
{
	if(s->startCol == 1 && s->endCol == t->colNum)
		drow(t,s,c); //if all columns in row => delete whole row
	else
	{
		int minus = (s->endCol+1) - s->startCol;

		for(int i = s->startRow-1 ; i < s->endRow ;i++)
		{
			for(int j = s->startCol-1; j+minus < t->colNum; j++)
			{
				c->row = i;
				c->col = j+minus;
				swap(t, c, i, j); //first move all cells
			}	
		}//then delete cells from the end of the row
		for(int i = s->startRow-1; i < s->endRow; i++)
		{
			for (int j = t->colNum-1; j >= t->colNum-minus; j--)
			{
				free(t->rows[i].cells[j].cell);
				t->rows[i].cells[j].cell = NULL;

				if(s->endCol == t->colNum && j == t->colNum-minus)	//index posledního znaku bunky   //+odebraný pocet bunek
					endCell(t->rows[i].cells[j-1].cell,j,t->rows[i].cells[j-1].celLength - 1,t->colNum - (minus-1), t->del);
			}			//poslední nevymazaná bunka  //j=t->colNum-minus => cislo té bunky
		}	
		t->colNum -= minus;
	}
}

//Sum and Avg is similiar and the code is almost the same, so it is better to have it in one function
void sumAvg(tab_t *t, changeSelection_t *s, commands_t *c, int i, int j)
{
	char *tmp;
	float num = strtof(t->rows[i].cells[j].cell, &tmp); //first variable to check if in the cell is number
	
	if(tmp[1] == '\0' && num != 0) //then check, if there is number
	{
		c->sumNum += num; //c->sumNum = c->sumNum + num;
		c->counter += 1.0; //counts how many numbers are there
	}

	if(i+1 == s->endRow && j+1 == s->endCol) //if last selected cell was checked => rewrite the right cell
	{
		char betterNum[13]; //11 is the biggest size of %g +1 delim +1 '\0'	
		if(c->sum == true)
			sum(betterNum, c->sumNum);
		else							//differences between sum and avg
			avg(betterNum, c);
		
		char *reall = realloc(t->rows[c->row].cells[c->col].cell, (strlen(betterNum)+1) * (sizeof(char) +2)); //realloc cell to the right size
		if(reall != NULL)
		{
			t->rows[c->row].cells[c->col].cell = reall;
			strcpy(t->rows[c->row].cells[c->col].cell,betterNum); //copy value to the cell
			endCell(t->rows[c->row].cells[c->col].cell, c->col, (strlen(betterNum)), t->colNum, t->del); //end check
			t->rows[c->row].cells[c->col].celLength = strlen(t->rows[c->row].cells[c->col].cell); //repair length of the cell
		}
	}
}
// sum [R,C] - do buňky na řádku R a sloupci C uloží součet hodnot vybraných buněk (odpovídající formátu %g u printf).
//Vybrané buňky neobsahující číslo budou ignorovány (jako by vybrány nebyly).
void sum(char *finalNum, float sum)
{
	int zk = sizeof(finalNum);
	int uselessVar = snprintf(finalNum, zk, "%g", sum);
	(void)uselessVar; //if uselessVar < 0 => error, but I know sum can be converted, because i checked that before calling this function
}
//avg [R,C] - stejné jako sum, ale ukládá se aritmetický průměr z vybraných buněk
void avg(char *finalNum, commands_t *c)
{
	int zk = sizeof(finalNum);
	int uselessVar = snprintf(finalNum, zk, "%g", c->sumNum/c->counter);
	(void)uselessVar;
}

//count [R,C] - stejné jako sum, ale ukládá se počet neprázdných buněk z vybraných buněk
void count(tab_t *t, commands_t *c, changeSelection_t *s, int i, int j)
{
	if(t->rows[i].cells[j].celLength == 1) //if celLength == 1 => it contains only delim/'\n' => empty cell
		c->counter++;
		
	if(i+1 == s->endRow && j+1 == s->endCol) //if last selected cell was checked => rewrite the right cell
	{
		char betterNum[t->rowsNum * t->colNum +1]; //max number of cells in tab + '\0'

		int uselessVar = snprintf(betterNum, sizeof(betterNum), "%g", c->counter);
		(void)uselessVar;
							//realloc selected cell
		char *reall = realloc(t->rows[c->row].cells[c->col].cell, (strlen(betterNum)+1) * (sizeof(char) +2));
		if(reall != NULL)
		{
			t->rows[c->row].cells[c->col].cell = reall;
			strcpy(t->rows[c->row].cells[c->col].cell,betterNum); //copy value to the cell
			endCell(t->rows[c->row].cells[c->col].cell, c->col, (strlen(betterNum)), t->colNum, t->del); //end check
			t->rows[c->row].cells[c->col].celLength = strlen(t->rows[c->row].cells[c->col].cell); //repair length of the cell
		}
	}
}

//clear - obsah vybraných buněk bude odstraněn (buňky budou mít prázdný obsah)
void clear(tab_t *t, int i, int j)
{	
	char *reall = realloc(t->rows[i].cells[j].cell, sizeof(char)+2); //realloc size of one char (delim / '\n')
	if(reall != NULL)
	{
		t->rows[i].cells[j].cell = reall;
		endCell(t->rows[i].cells[j].cell, j, 0, t->colNum, t->del); //end check
		t->rows[i].cells[j].celLength = strlen(t->rows[i].cells[j].cell); //repair length
	}
}

//set STR - nastaví hodnotu buňky na řetězec STR. Řetězec STR může být ohraničen uvozovkami a může obsahovat speciální znaky uvozené lomítkem (viz formát tabulky)
void setStr(tab_t *t, commands_t *c, int i, int j)
{													//lenght of STR + 1 (for delim)		+ 2(\0)
	char *reall = realloc(t->rows[i].cells[j].cell, (strlen(c->setStr)+1)*((sizeof(char)) + 2));
	if(reall != NULL)
	{
		t->rows[i].cells[j].cell = reall;
		strcpy(t->rows[i].cells[j].cell, c->setStr); //copy STR to cell
		endCell(t->rows[i].cells[j].cell, j, strlen(c->setStr), t->colNum, t->del); //end check
		t->rows[i].cells[j].celLength = strlen(t->rows[i].cells[j].cell); //repair length
	}
}

//len [R,C] - do buňky na řádku R a sloupci C uloží délku řetězce aktuálně vybrané buňky
int len(tab_t *t, changeSelection_t *s, commands_t *c, int i, int j)
{
	if(s->startRow != s->endRow || s->startCol != s->endCol)
	{	
		fprintf(stderr, "You can take length of only one cell!\n");
		return 1;
	}
	else
	{
		int length = t->rows[i].cells[j].celLength;
   		int count = 0;
		int countDig = length;
   		while (countDig != 0){	//counts number of digits of length for realloc
        	countDig /= 10;
        	++count;
		}
		char *reall = realloc(t->rows[c->row].cells[c->col].cell, count*sizeof(char)+2);
		if(reall != NULL)
		{
			t->rows[c->row].cells[c->col].cell = reall;
			char setLen[count+1];
			int uselessVar = snprintf(setLen, sizeof(setLen), "%d", length-1); //convert length to char[] for strcpy()
			(void)uselessVar;
			strcpy(t->rows[c->row].cells[c->col].cell, setLen); //copy
			endCell(t->rows[c->row].cells[c->col].cell, c->col, strlen(setLen), t->colNum, t->del); //end check
			t->rows[c->row].cells[c->col].celLength = strlen(t->rows[c->row].cells[c->col].cell); //repair length
		}
		else{
			fprintf(stderr, "Wrong realloc\n");
			return 1;
		}	
	}
	return 0;
}

//def _X - hodnota aktuální buňky bude nastavena do dočasné proměnné X (kde X může být hodnota 0 až 9)
void def(tab_t *t, changeSelection_t *s, tempVariables_t *v)
{
	char *reall = realloc(v->temp, sizeof(t->rows[s->endRow-1].cells[s->endCol-1].cell) + 2); //realloc - temp variable
	if(reall != NULL)
	{
		v->temp = reall;
		strcpy(v->temp, t->rows[s->endRow-1].cells[s->endCol-1].cell); //copy cell to temp
	}
	v->temp[strlen(v->temp)-1] = '\0';
}
//use _X - aktuální buňka bude nastavena na hodnotu z dočasné proměnné X (kde X identifikuje dočasnou proměnnou _0 až _9)
void use(tab_t *t, changeSelection_t *s, char *temp)
{
	commands_t c = {};
	strcpy(c.setStr,temp);
	c.setStr[strlen(temp)] = '\0';
	if(temp != NULL)
	{
		for(int i = s->startRow-1; i < s->endRow; i++)
		{
			for(int j = s->startCol-1; j < s->endCol; j++)
			{
				setStr(t,&c,i,j); //because i have a function to set str, i need to write it again
			}
		}
	}
}
//inc _X - numerická hodnota v dočasné proměnné bude zvětšena o 1. Pokud dočasná proměnná neobsahuje číslo, bude výsledná hodnota proměnné nastavená na 1.
void inc(tempVariables_t *v)
{	
	if(v->temp[0] == '\0') //if temp != number
	{
		char *reall = realloc(v->temp, sizeof(char) + 2);  //realloc temp
		if(reall != NULL)
		{
			v->temp = reall;
			v->temp[0] = '1'; //set temp to 1
			v->temp[1] = '\0'; //end tem with '\0'
		}
	}
	else{ //temp == number
			int value = strtol(v->temp, NULL, 10); //find out value
			value = snprintf(v->temp, sizeof(int), "%d", value+1); //repair temp to value + 1
	}
}
//if end cell in every row is empty => delete that column
void noEmptyCol(tab_t *t)
{
	changeSelection_t s = {1,1,1,t->rowsNum};
	commands_t com = {}; //this is here just because i need to fill the last parameter in dcol  

	bool isEmpty = true;
	for(int i = t->colNum-1; isEmpty != false; i--) //until some cell in last column isnt empty
	{
		for(int j = 0; j < t->rowsNum; j++){ //check the whole column
			if(t->rows[j].cells[i].celLength != 1) //if cell isn't empty
			{
				isEmpty = false; //=> not empty => don't need to control the rest
				break;
			}
		}
		if(isEmpty == true) //=> delete last column
		{
			s.startCol = i+1;
			s.endCol = t->colNum;
			dcol(t,&s,&com);
		}
	}
}
//in final file, there dont have to be "", so delete them
void deleteQuotatM(tab_t *t)
{
	for(int i = 0; i < t->rowsNum; i++)
	{
		for(int j = 0; j < t->colNum; j++)
		{
			if(strstr(t->rows[i].cells[j].cell, "\"")) //if cell contains ""
			{
				char repaired[t->rows[i].cells[j].celLength-2]; // (- " ") => -2
				int l = 0;
				for(int k = 0; k < t->rows[i].cells[j].celLength; k++) //copy cell without ""
				{
					if(t->rows[i].cells[j].cell[k] == '\"')
						continue;
					repaired[l] = t->rows[i].cells[j].cell[k];
					l++;
				}
				repaired[l] = '\0';
													//realloc cell to length of the cell - 2 ("")
				char *reall = realloc(t->rows[i].cells[j].cell, strlen(repaired)*sizeof(char) + 2);
				if(reall != NULL)
				{
					t->rows[i].cells[j].cell = reall;
					strcpy(t->rows[i].cells[j].cell, repaired); //copy cell without "" to cell
				}	//its not necessary to repair length, because i wont work with sigle cells anymore
			}
		}
	}
}
//write tab to the file
void writeToFile(arguments_t *a, tab_t *t)
{
	FILE *fp;
	fp = fopen(a->argv[a->argc-1] , "w"); //dont need to check all the things about stdin again, exit would have been called already
   	if(fp == NULL) 
   	{
    	fprintf(stderr, "Error opening file\n");
		myExit(t);
   	}

	for(int i = 0; i < t->rowsNum; i++)
		for(int j = 0; j < t->colNum; j++)
			fprintf(fp, "%s", t->rows[i].cells[j].cell);
	
	fclose(fp); //need to close that file again
}
//function to free alloced memory for temporary variables
void freeTempVar(tempVariables_t *v)
{
	free(v->_0);
	free(v->_1);
	free(v->_2);
	free(v->_3);
	free(v->_4);
	free(v->_5);
	free(v->_6);
	free(v->_7);
	free(v->_8);
	free(v->_9);
}
//function to free alloced memory for table
void freeAll(tab_t *t)
{
	if(t!=NULL)
	{
		for(int i = 0; i < t->rowsNum; i++)
		{
			for(int j = 0; j < t->colNum; j++)	//first i need to free memory for cells
			{
				free(t->rows[i].cells[j].cell);
				t->rows[i].cells[j].cell = NULL;
			}
			free(t->rows[i].cells); //then i need to free memory for columns
			t->rows[i].cells = NULL;
		}
		free(t->rows); //in the end i need to free memory for rows
		t->rows = NULL;
	}
}