#pragma once
void printWord(char completeWord[],char letter, char currentStateWord[], int gameHasStarted);
void printHangMan(int mistake, int difficulty, char hangedMan[]);
int detectWin(char currentStateWord[], char completeWord[]);