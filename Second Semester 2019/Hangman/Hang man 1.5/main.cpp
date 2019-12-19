#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hangMan.h"

int main() {
	//Initializations
	enum Boolean{False,True};
	enum WinStates{Incomplete,Lose,Win};
	enum Gamemodes{Random=1,Type=2};
	enum DifficultyLevels{Easy=1,Hard=2};

	char completeWord[32] = {}; //The word for reference
	char currentStateWord[32] = {}; //The word right now (For the "_ _ _ _")
	char letter = '_'; //The letter chosen by the player
	char hangedMan[26] = {
	' ',' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',' ' };//Array used to create the hangedman

	int gameHasStarted = False; //To differentiate between first turn and the next ones
	int detectMistake = False; //To detect mistakes
	int mistake = 0; //The number of mistakes made. For the printHangMan.
	int winState = Incomplete; //For win states

	//For the "Do you know the word already?"
	int doKnowWord; //0: False, 1: True
	char guessedWord[32] = {}; //The guessed word from the player
	int isCorrect = 0; //Checks if guessedWord is the same as completeWord
	int correctValue = 0; //The value that isCorrect should have

	//Instructions
	printf("HANGMAN 1.5\n");
	printf("How this game works: \n");
	printf("1. Type a letter each time (ALL IN LOWERCASE)\n");
	printf("2. If you know the word, try and guess it!\n");
	printf("You have:\n- 10 mistakes on easy mode.\n- 6 mistakes on hard mode.\nGood Luck!\n\n");

	//Gamemode
	printf("Select gamemode:\n");
	printf("1. Random Word Generated (up to 84 words!)\n");
	printf("2. Type your own words.\n");
	printf("Type here: ");
	int gamemode;
	scanf("%d", &gamemode);
	
	//Random word Generator
	if (gamemode == Random) {
		srand(time(0));
		char dictionary[84][31]{
		{"gamer"},{"furry"},{"caterpillar"},{"weeaboo"},{"incel"},{"rainbow"},
		{"minecraft"},{"pikachu"},{"pokemon"},{"zelda"},{"inazuma eleven"},{"queen"},
		{"depression"},{"yoshi"},{"ganondorf"},{"fortnite"},{"rowlet"},{"fuck my life"},
		{"random"},{"placeholder"},{"anxiety"},{"bohemian"},{"netflix"},{"twitter"},
		{"microsoft"},{"john romero"},{"doom"},{"steam"},{"supernova"},{"hollow knight"},
		{"earthbound"},{"creeper"},{"pumpkin"},{"metal gear solid"},{"cheese"},{"chocolate"},
		{"fox mccloud"},{"youtube"},{"google"},{"microsoft"},{"goose"},{"apache attack helicopter"},
		{"totodile"},{"graphic design is my passion"},{"cosine"},{"lofi hip hop beats to relax"},{"kingdom hearts"},
		{"hideo kojima"},{"dragon ball"},{"neon genesis evangelion"},{"attack on titan"},{"wake me up when september ends"},{"the simpsons"},
		{"waluigi"},{"league of legends"},{"odyssey"},{"nintendo"},{"franco"},{"homestuck"},
		{"undertale"},{"bootleg"},{"ahegao"},{"hentai"},{"half life"},{"shadow of the colossus"},
		{"majora"},{"discord"},{"patreon"},{"switch"},{"visual studio"},{"i should be sleeping"},
		{"skull kid"},{"spooky scary skeletons"},{"wubba lubba dub dub"},{"rainbow dash"},{"my little ponny"},{"nvidia"},
		{"deltarune"},{"hotline miami"},{"overwatch"},{"layton"},{"kiwi"},{"adorable"}
		};
		int wordChosen = rand() % 84;
		for (int i = 0; dictionary[wordChosen][i] != '\0'; i++) {
			completeWord[i] = dictionary[wordChosen][i];
		}
	}

	//Type your word mode
	else if (gamemode == Type) {
		printf("Type the word (Max: 32 lowercase letters): ");
		scanf("%s", completeWord);
	}

	//Difficulty level
	printf("\nSelect difficulty: \n");
	printf("1. Easy mode\n");
	printf("2. Hard mode\n");
	printf("Type here: ");
	int difficulty;
	scanf("%d", &difficulty);

	//Turn Dev
	while (winState == Incomplete) {
	nextTurn:
		detectMistake = True;
		system("cls");
		printWord(completeWord, letter, currentStateWord, gameHasStarted);
		printHangMan(mistake, difficulty, hangedMan);
		
		//Win detection
		if (detectWin(currentStateWord, completeWord) == Win) {
			winState = Win;
			goto finalMessage;
		}
		else if (difficulty == Hard) {
			if (mistake == 6) {
				winState = Lose;
				goto finalMessage;
			}
		}
		else if (difficulty == Easy) {
			if (mistake == 10) {
				winState = Lose;
				goto finalMessage;
			}
		}

		//Do you know the word? (Only happens after first turn)
		if (gameHasStarted == True) {
			printf("Do you know the word?(Yes:1/No:Type letter directly[or type 0]) ");
			scanf("%d", &doKnowWord);
			if (doKnowWord == True) {
				printf("Try and guess it! ");
				scanf("%s", guessedWord);
				for (int i = 0; guessedWord[i] != '\0'; i++) {
					if (guessedWord[i] == completeWord[i]) {
						isCorrect++;
					}
					correctValue++;
				}

				if (isCorrect == correctValue) {
					for (int i = 0; completeWord[i] != '\0'; i++) {
						currentStateWord[i] = completeWord[i];
					}
				}
				else {
					mistake++;
				}
				goto nextTurn;
			}
		}

		gameHasStarted = True;

		//Type a letter
		printf("Type a letter: ");
		scanf(" %c", &letter);
		for (int i = 0; completeWord[i] != '\0'; i++) {
			if (completeWord[i] == letter) {
				detectMistake = False;
				currentStateWord[i] = letter;
			}
		}

		if (detectMistake == False) {
			goto nextTurn;
		}
		mistake++;
	}

	//Ending Message
finalMessage:
	if (winState == Win) {
		printf("You won, congratulations!\n");
	}
	else if (winState == Lose) {
		printf("You lost. Better luck next time!\n");
		printf("The correct word was %s.\n\n", completeWord);
	}
	system("pause");
	return 0;
}