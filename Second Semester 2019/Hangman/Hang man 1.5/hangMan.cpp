#include <stdio.h>
#include <stdlib.h>

void printWord(char completeWord[], char letter, char currentStateWord[], int gameHasStarted) {
	//First turn print
	if (gameHasStarted != 1) {
		for (int i = 0; completeWord[i] != '\0'; i++) {
			currentStateWord[i] = '_';
			if (completeWord[i] == ' ') {
				currentStateWord[i] = ' ';
			}
			printf("%c ", currentStateWord[i]);
		}
	}
	//Next turn prints
	else {
		for (int i = 0; completeWord[i] != '\0'; i++) {
			if (completeWord[i] == letter) {
				currentStateWord[i] = letter;
			}
			printf("%c ", currentStateWord[i]);
		}
	}
	printf("\n\n");
}

void printHangMan(int mistake, int difficulty, char hangedMan[]) {
	//Hard mode
	if (difficulty == 2) {
		//Stand
		for (int i = 0; i < 9; i++) {
			hangedMan[i] = '=';
		}
		for (int i = 0; i < 5; i++) {
			hangedMan[i + 9] = '|';
		}
		hangedMan[14] = '+';
		hangedMan[18] = '+';
		for (int i = 15; i < 18; i++) {
			hangedMan[i] = '=';
		}
		hangedMan[19] = '|';
		
		//Person printer
		if (mistake == 0) {
			goto proceed;
		}
		else if (mistake == 1) {
			hangedMan[20] = 'O';
		}
		else if (mistake == 2) {
			hangedMan[21] = '/';
		}
		else if (mistake == 3) {
			hangedMan[22] = '|';
		}
		else if (mistake == 4) {
			hangedMan[23] = '\\';
		}
		else if (mistake == 5) {
			hangedMan[24] = '/';
		}
		else if (mistake == 6) {
			hangedMan[25] = '\\';
		}
	}
	//Easy mode
	else if (difficulty == 1) {
		if (mistake == 0) {
			goto proceed;
		}
		else if (mistake == 1) {
			for (int i = 0; i < 9; i++) {
				hangedMan[i] = '=';
			}
		}
		else if (mistake == 2) {
			for (int i = 0; i < 5; i++) {
				hangedMan[i+9] = '|';
			}
		}
		else if (mistake == 3) {
			hangedMan[14] = '+';
			hangedMan[18] = '+';
			for (int i = 15; i < 18; i++) {
				hangedMan[i] = '=';
			}
		}
		else if (mistake == 4) {
			hangedMan[19] = '|';
		}
		else if (mistake == 5) {
			hangedMan[20] = 'O';
		}
		else if (mistake == 6) {
			hangedMan[21] = '/';
		}
		else if (mistake == 7) {
			hangedMan[22] = '|';
		}
		else if (mistake == 8) {
			hangedMan[23] = '\\';
		}
		else if (mistake == 9) {
			hangedMan[24] = '/';
		}
		else if (mistake == 10) {
			hangedMan[25] = '\\';
		}
	proceed:
		printf("  %c%c%c%c%c\n",hangedMan[14],hangedMan[15],hangedMan[16],hangedMan[17],hangedMan[18]);
		printf("  %c   %c\n", hangedMan[19], hangedMan[13]);
		printf("  %c   %c\n", hangedMan[20], hangedMan[12]);
		printf(" %c%c%c  %c\n", hangedMan[21], hangedMan[22], hangedMan[23], hangedMan[11]);
		printf(" %c %c  %c\n", hangedMan[24], hangedMan[25], hangedMan[10]);
		printf("      %c\n", hangedMan[9]);
		printf("%c%c%c%c%c%c%c%c%c\n", hangedMan[0], hangedMan[1], hangedMan[2], hangedMan[3], hangedMan[4], hangedMan[5], hangedMan[6], hangedMan[7], hangedMan[8]);
	}
}

int detectWin(char currentStateWord[], char completeWord[]) {
	int detectWin = 0;
	int lengthWord = 0;
	for (int i = 0; currentStateWord[i] != '\0'; i++) {
		if (currentStateWord[i] == completeWord[i]) {
			detectWin++;
		}
		lengthWord++;
	}
	if (detectWin == lengthWord) {
		return 2;
	}
	else {
		return 0;
	}
}