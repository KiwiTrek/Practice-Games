#include <stdio.h>
#include <stdlib.h>

void printWord(char completeWord[], char letter, int letterDetect, char currentStateWord[], int gameHasStarted) {
	if (gameHasStarted != 1) {
		for (int i = 0; completeWord[i] != '\0'; i++) {
			currentStateWord[i] = '_';
			if (completeWord[i] == ' ') {
				currentStateWord[i] = ' ';
			}
			printf("%c ", currentStateWord[i]);
		}
		gameHasStarted = 1;
	}
	else {
		if (letterDetect == 1) {
			for (int i = 0; completeWord[i] != '\0'; i++) {
				if (completeWord[i] != '_') {
					if (completeWord[i] == letter) {
						currentStateWord[i] = letter;
					}
				}
				else {
					currentStateWord[i] = '_';
				}
				printf("%c ", currentStateWord[i]);
			}
		}
		else {
			for (int i = 0; completeWord[i] != '\0'; i++) {
				if (currentStateWord[i] != '_') {
					goto printf;
				}
				currentStateWord[i] = '_';
				printf:
				printf("%c ", currentStateWord[i]);
			}
		}
	}
	printf("\n");
	printf("\n");
}

void printHangMan(char word[], char letter, int mistake, int gameHasStarted) {
	char hangedMan[6] = { ' ',' ',' ',' ',' ',' ' };
	if (gameHasStarted != 1) {
		printf("  +---+\n");
		printf("  |   |\n");
		printf("      |\n");
		printf("      |\n");
		printf("      |\n");
		printf("      |\n");
		printf("=========\n");
	}
	else {
		if (mistake == 0) {
			goto proceed;
		}
		else if (mistake == 1) {
			hangedMan[0] = 'O';
		}
		else if (mistake == 2) {
			hangedMan[0] = 'O';
			hangedMan[1] = '/';

		}
		else if (mistake == 3) {
			hangedMan[0] = 'O';
			hangedMan[1] = '/';
			hangedMan[2] = '|';
		}
		else if (mistake == 4) {
			hangedMan[0] = 'O';
			hangedMan[1] = '/';
			hangedMan[2] = '|';
			hangedMan[3] = '\\';
		}
		else if (mistake == 5) {
			hangedMan[0] = 'O';
			hangedMan[1] = '/';
			hangedMan[2] = '|';
			hangedMan[3] = '\\';
			hangedMan[4] = '/';
		}
		else if (mistake == 6) {
			hangedMan[0] = 'O';
			hangedMan[1] = '/';
			hangedMan[2] = '|';
			hangedMan[3] = '\\';
			hangedMan[4] = '/';
			hangedMan[5] = '\\';
		}
		proceed:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  %c   |\n",hangedMan[0]);
		printf(" %c%c%c  |\n",hangedMan[1],hangedMan[2],hangedMan[3]);
		printf(" %c %c  |\n",hangedMan[4],hangedMan[5]);
		printf("      |\n");
		printf("=========\n");
	}
}

int detectWin(char currentStateWord[], char completeWord[]) {
	int detectWin = 0;
	int lengthWord = 0;
	for (int i = 0; completeWord[i] != '\0'; i++) {
		lengthWord++;
	}
	for (int i = 0; currentStateWord[i] != '\0'; i++) {
		if (currentStateWord[i] == completeWord[i]) {
			detectWin++;
		}
	}
	if (detectWin == lengthWord) {
		return 2;
	}
	else {
		return 0;
	}
}