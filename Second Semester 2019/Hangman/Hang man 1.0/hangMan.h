#pragma once
void printWord(char completeWord[],char letter, int letterDetect, char currentStateWord[], int gameHasStarted);
void printHangMan(char word[], char letter, int mistake, int gameHasStarted);
int detectWin(char currentStateWord[], char completeWord[]);