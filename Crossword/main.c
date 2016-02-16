#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constantes del programa
#define WORDS 13
#define MAX_X 18
#define MAX_Y 24


//Structure of Player
struct Player{
	char name[50], lastName[50], ID[50], address[50], phone[50], genre[50];
	int  age;
};
struct Word{
	int ID, posx, posY;
	char orientation, solution[50];
};


//Prototipos de funciones
void chooseLevel();
void setFilesByLevel(int option);
void createGame(char crossWord[MAX_X][MAX_Y]);
void welcomeMessage();
void initMessage();
struct Player inputInfo();
void inputInfoPlayers();
void createCrossWord(char crossword[MAX_X][MAX_Y]);
void printCrossWord(char crossword[MAX_X][MAX_Y], int scoreP1 , int scoreP2);
void readFile(char crossWord[MAX_X][MAX_Y]);
void fillCrossWordWithSpaces(char crossWord[MAX_X][MAX_Y],char word[50],char orientation,int posX, int posY);
int getNumberOfElements(char word[]);
struct Word obtainWordToShowInGame(int numWord);
void fillCrossWordWithWords(char crossWord[MAX_X][MAX_Y],char word[50],char orientation,int posX, int posY);
void inputToPlay(char *word, int *numWord);
int isCorrectAnswer(char *wordInBank, char *inputWord);
void loadClues();
void putLabelsOnWords(char crossword[MAX_X][MAX_Y]);
int verifyWord(char *word);
void printResults(int scoreP1, int scoreP2);

//Global Variables
struct Player playerOne, playerTwo;
struct Word words[WORDS];
struct Word answeredWords[WORDS];
char *file_words;
char *file_clues;
int levelOfGame;

int main(){
	char crossWord[MAX_X][MAX_Y], word[50];
	int turn = 1, endOfGame = 0, numWord,scoreP1= 0, scoreP2 =0, totalWords = 0, indicator =0,option;
	struct Word wordInBank;
	chooseLevel();
	createGame(crossWord);
	printCrossWord(crossWord,scoreP1, scoreP2);
	while(endOfGame != 1){
		if( turn ==1){
			printf("\nPLAYER 1:");
			inputToPlay(word, &numWord);
			wordInBank = obtainWordToShowInGame(numWord-1);
			if(isCorrectAnswer(wordInBank.solution,word) == 1 ){// La palabra es correcta
				if(verifyWord(word) == 0){
					printf("\n\nCorrecto! Ud. suma 10 puntos!\n\n");
					fillCrossWordWithWords(crossWord,wordInBank.solution,wordInBank.orientation,wordInBank.posx, wordInBank.posY);
					scoreP1 = scoreP1 + 10;
					totalWords= totalWords +1;
					strcpy(answeredWords[indicator].solution , word);
					indicator++;
				}else{
					printf("\n\nYa ha sido respondida. Pierde puntos!\n\n");
					scoreP1 = scoreP1 - 10;
				}
			}else{
				printf("\n\nRespuesta Invalida!\n\n");
				scoreP1 = scoreP1 - 10;
			}
			system("\n\n\t\tPAUSE");
			turn=2;
		}else{
			printf("\nPLAYER 2:");
			inputToPlay(word, &numWord);
			wordInBank = obtainWordToShowInGame(numWord-1);
			if(isCorrectAnswer(wordInBank.solution,word) == 1 ){// La palabra es correcta
				if(verifyWord(word) == 0){
					printf("\n\nCorrecto! Ud. suma 10 puntos!\n\n");
					fillCrossWordWithWords(crossWord,wordInBank.solution,wordInBank.orientation,wordInBank.posx, wordInBank.posY);
					scoreP2 = scoreP2 + 10;
					totalWords= totalWords +1;
					strcpy(answeredWords[indicator].solution , word);
					indicator++;
				}else{
					printf("\n\nYa ha sido respondida. Pierde puntos!\n\n");
					scoreP2 = scoreP2 - 10;
				}
			}else{
				printf("\n\nRespuesta Invalida! Pierde 10 puntos\n\n");
				scoreP2 = scoreP2 - 10;
			}
			system("\n\n\t\tPAUSE");
			turn=1;
		}
		system("cls");
		printCrossWord(crossWord, scoreP1, scoreP2);
		if(totalWords >= 12) //Ya no hay palabras que adivinar
			endOfGame = 1;
	}
	printResults(scoreP1, scoreP2);

}


void createGame(char crossWord[MAX_X][MAX_Y]){
	initMessage();
	printf("\n\n\n\n\n");
	createCrossWord(crossWord);
	readFile(crossWord);
	system("cls");

}
void initMessage(){
	welcomeMessage();
	inputInfoPlayers();
	
}

void welcomeMessage(){
	printf("\t\t\t\tWELCOME\n");
	printf("\t\t\tGAME OF CROSSWORD\n\n");
	printf("\t\tPlayers, enter your information\n\n\n");
}

struct Player inputInfo(){
	struct Player p;
	char name[50], lastName[50], ID[50], address[50], phone[50], genre[50];
	int  age;
	printf("\tName: ");
	fgets(name, 50, stdin);
	fflush(stdin);
	strcpy(p.name,name);
	printf("\tLast Name: ");
	fgets(lastName, 50, stdin);
	fflush(stdin);
	strcpy(p.lastName,lastName);
	printf("\tID: ");
	fgets(ID, 50, stdin);
	fflush(stdin);
	strcpy(p.ID,ID);
	printf("\tDirection: ");
	fgets(address, 50, stdin);
	fflush(stdin);
	strcpy(p.address,address);
	printf("\tPhone: ");
	fgets(phone, 50, stdin);
	fflush(stdin);
	strcpy(p.phone,phone);
	printf("\tEdad: ");
	scanf("%d",&p.age);
	fflush(stdin);
	printf("\tGenre:");
	gets(genre); 
	fflush(stdin);
	strcpy(p.genre,genre);
	return p;
}

void inputInfoPlayers(){
	printf("Player 1:\n");
	playerOne = inputInfo();
	printf("\n\nPlayer 2:\n");
	playerTwo = inputInfo();
	printf("\n\t\t\t");
	system("PAUSE");
}

void createCrossWord(char crossword[MAX_X][MAX_Y]){
	int i,j;
	for(i =0; i<MAX_X; i++){
		for(j=0; j<MAX_Y; j++){
			crossword[i][j] = '.';
		}
	}
	putLabelsOnWords(crossword);
}

void printCrossWord(char crossword[MAX_X][MAX_Y], int scoreP1 , int scoreP2 ){
	int i,j;
	printf("\tPLAYER 1: %d ptos", scoreP1);
	printf("\t\t\t\tPLAYER 2: %d ptos\n\n",scoreP2);
	printf("\t\t");
	for(i =0; i<MAX_X; i++){
		for(j=0; j<MAX_Y; j++){
			printf("%c ", crossword[i][j]);
		}
		printf("\n\t\t");
	}
	loadClues();
}

void readFile(char crossWord[MAX_X][MAX_Y]){
	FILE *file;
	char line[100];
	int id = 0 ,posX = 0,posY = 0,cont = 0;
	char word[50],orientation;
	char lineWithSpace[50] = "PUNTO Y APARTE";
	file = fopen(file_words,"r");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
	}else{
		while (feof(file) == 0){
			fscanf(file,"%d,%c,%d,%d,%s",&id,&orientation,&posX,&posY,word);
			if(strcmp("PUNTOYAPARTE",word) == 0)
				strcpy(word, lineWithSpace);
			words[id-1].ID = id;
			words[id-1].orientation = orientation;
			words[id-1].posx = posX;
			words[id-1].posY = posY;
			strcpy ( words[id-1].solution, word); 
			fillCrossWordWithSpaces(crossWord,word,orientation,posX,posY);
	    }
	}
	fclose(file);
}

void fillCrossWordWithSpaces(char crossWord[MAX_X][MAX_Y],char word[50],char orientation,int posX, int posY){
	int i=0, size = getNumberOfElements(word);
	if(orientation == 'H'){
		for(i ==0; i<size; i++){
			crossWord[posX][posY+i] = 'o';
		}
	}else if(orientation == 'V'){
		for(i ==0; i<size; i++){
			crossWord[posX+i][posY] = 'o';
		}
	}
}

int getNumberOfElements(char word[]){
	int i =0;
	while(word[i]!='\0'){
		i++;
	}
	return i;
}


//Funcion que pide por teclado una palabra para el crossword
int obtainOptionToPlay(){
	int option;
	printf("\n\nIngrese el # de la pista: ");
	scanf("%d",&option);
	return option;
}


void obtainWordToPlay(int op, char *word){
	printf("\n\nIngrese la solucion de la pista #%d : ",op);
	scanf("%s",word);
}


struct Word obtainWordToShowInGame(int numWord){
	return words[numWord];
}

//Funcion que dada la palabra correcta de la solucion, la ubica en el tablero LLAMARLA EN EL JUEGO
void fillCrossWordWithWords(char crossWord[MAX_X][MAX_Y],char word[50],char orientation,int posX, int posY){
	int i=0, size = getNumberOfElements(word);
	if(orientation == 'H'){
		for(i ==0; i<size; i++){
			crossWord[posX][posY+i] = word[i];
		}
	}else if(orientation == 'V'){
		for(i ==0; i<size; i++){
			crossWord[posX+i][posY] = word[i];
		}
	}
}

int isCorrectAnswer(char *wordInBank, char *inputWord){
	if(strcmp(wordInBank,inputWord)== 0)
		return 1;
	return 0;
}

void inputToPlay(char *word, int *numWord){
	printf("\n\nIngrese el # de la pista que quiere resolver: ");
	scanf("%d",numWord);
	fflush(stdin);
	printf("Ingrese la solucion de la pista #%d : ",*numWord);
	//scanf("%s",word);
	gets(word);
	word = strupr(word);
}

void loadClues(){
	FILE *file;
	int i = 0;
	char line[300];
	file = fopen(file_clues,"r");
	printf("\n\PISTAS:\n\n");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
	}else{
		while (feof(file) == 0){
			fgets(line,300,file);
			printf("%s", line);
	    }
	}
	fclose(file);
}

void putLabelsOnWords(char crossword[MAX_X][MAX_Y]){
	if(levelOfGame ==1){
		crossword[5][1] = '1';
		crossword[2][11] = '2';
		crossword[2][0] = '3';
		crossword[3][2] = '4';
		crossword[9][3] = '5';
		crossword[0][5] = '6';
		crossword[3][9] = '7';
		crossword[4][13] = '8';
		crossword[1][9] = '9';
		crossword[6][7] = '@';
		crossword[14][8] = '#';
		crossword[5][18] = '$';
		crossword[7][15] = '+';
	}else{
		crossword[0][2] = '1';
		crossword[0][13] = '2';
		crossword[2][0] = '3';
		crossword[1][5] = '4';
		crossword[2][4] = '5';
		crossword[5][7] = '6';
		crossword[5][9] = '7';
		crossword[5][11] = '8';
		crossword[10][0] = '9';
		crossword[9][4] = '@';
		crossword[14][0] = '#';
		crossword[14][9] = '$';
		crossword[4][1] = '+';
	}
}


int countAnsweredWords(){
	int i, cont =0 ;
	for(i=0;i<WORDS;i++){
		cont++;
	}
	return cont;
}
int verifyWord(char *word){ //Retorno 1 si la palabra ya ha sido contestada, 0 si no.
	int i, cont;
	for(i=0;i<WORDS;i++){
		if(strcmp(answeredWords[i].solution, word) == 0){
			return 1;
		}
	}
	return 0; //Es una respuesta que no se ha contestado
}

void printResults(int scoreP1, int scoreP2){
	system("cls");
	printf("\n\t\t\tFIN DE JUEGO");
	printf("\n\n\t\t%s: %d ptos",playerOne.name, scoreP1);
	printf("\n\n\t\t%s: %d ptos"),playerTwo.name, scoreP2;
	if(scoreP1 > scoreP2) //Gano Jugador 1
		printf("\n\n\tGANA %s!",playerOne.name);
	else
		printf("\n\n\tGANA %s!", playerTwo.name);
	system("PAUSE");
}


void chooseLevel(){
	int option=0;
	while(option !=1 && option!=2){
		printf("\n\n\t\t\tGAME OF CROSSWORD");
		printf("\n\n\t\tEscoga el nivel que desee:");
		scanf("%d", &option);
		fflush(stdin);
	}
	system("cls");
	setFilesByLevel(option);
}

void setFilesByLevel(int option){
	if (option ==1){
		file_clues = "clues.txt";
		file_words = "words.txt";
		levelOfGame = 1;
	}else{
		file_clues = "clues_level2.txt";
		file_words = "words_level2.txt";
		levelOfGame = 2;
	}
}