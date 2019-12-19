#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hangMan.h"

int main() {
	//Initializations
	enum Boolean{False,True};
	enum WinStates{Incomplete,Lose,Win};
	
	//Words and letters
	char completeWord[32] = {};
	char currentStateWord[32] = {};
	char letter = '_';

	//For checking wins
	int gameHasStarted = False;
	int letterDetect = False;
	int mistake = 0;
	int winState = Incomplete;

	//For guessing word
	int doKnowWord;
	int isCorrect = 0;
	char guessedWord[32] = {};
	int length = 0;

	//Instructions
	printf("HANGMAN 1.0\n");
	printf("How this game works: \n");
	printf("1. Get someone else to put a word for you.\n");
	printf("2. Type a letter each time (ALL IN LOWERCASE)\n");
	printf("-You have 6 mistakes.\nGood Luck!\n\n");
	printf("Select gamemode:\n");
	printf("1. Random Word Generated (up to 84 words!)\n");
	printf("2. Type your own words.\n");

	//Gamemode
	printf("Type here: ");
	int gamemode;
	scanf("%d", &gamemode);
	if (gamemode == 1) {
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
		int wordChosen = rand() % 50;
		for (int i = 0; dictionary[wordChosen][i] != '\0'; i++) {
			completeWord[i] = dictionary[wordChosen][i];
		}
	}
	else if (gamemode == 2) {
		printf("Type the word (Max: 32 lowercase letters): ");
		scanf("%s", completeWord);
	}

	//Turn Dev
	while (winState == Incomplete) {
	
	nextTurn:
		system("cls");
		printWord(completeWord, letter, letterDetect, currentStateWord, gameHasStarted);
		printHangMan(completeWord, letter, mistake, gameHasStarted);
		if (detectWin(currentStateWord, completeWord) == Win) {
			winState = Win;
			goto finalMessage;
		}
		else if (mistake == 6) {
			winState = Lose;
			goto finalMessage;
		}

		//Do you know the word? (WIP)
		if (gameHasStarted == 1) {
			printf("Do you know the word?(1:Yes/0:No) ");
			scanf("%d", &doKnowWord);
			if (doKnowWord == True) {
				printf("Try and guess it! ");
				scanf("%s", guessedWord);
				for (int i = 0; guessedWord[i] != '\0'; i++) {
					if (guessedWord[i] == completeWord[i]) {
						isCorrect++;
					}
					length++;
				}
				if (isCorrect == length) {
					for (int i = 0; completeWord[i] != '\0'; i++) {
						currentStateWord[i] == completeWord[i];
					}
					goto nextTurn;
				}
				else {
					goto mistaken;
				}
			}
		}

		gameHasStarted = 1;

		//Type a letter
		printf("Type a letter: ");
		scanf(" %c", &letter);
		for (int i = 0; completeWord[i] != '\0'; i++) {
			if (completeWord[i] == letter) {
				letterDetect = True;
				for (int i = 0; completeWord[i] != '\0'; i++) {
					if (completeWord[i] == letter) {
						currentStateWord[i] = letter;
					}
				}
				goto nextTurn;
			}
		}
	mistaken:
		mistake++;
		letterDetect = False;
	}

	//Ending Message
finalMessage:
	if (winState == Win) {
		printf("You won, congratulations!\n");
	}
	else if (winState == Lose) {
		printf("You lost. Better luck next time!\n");
		printf("The correct word was %s.\n", completeWord);
	}
	system("pause");
	return 0;
}