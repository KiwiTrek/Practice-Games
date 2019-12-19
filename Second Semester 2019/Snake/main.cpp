#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAX_X 20
#define MAX_Y 10

enum Flags {
	isStillPlaying = 1 << 1,
	isObtained = 1 << 2,
	headDetected = 1 << 3
};
enum Directions {
	UP, DOWN, LEFT, RIGHT
};

struct Fruit {
	unsigned char flags;
	int x, y;
};
struct Snek {
	unsigned char flags;
	int x, y;
	int TailX[32], TailY[32];
};

//Instructions
void printInstructions() {
	printf("   __oo_             __      \n");
	printf("  / ___/-<__  ____ _/ /_____ \n");
	printf("  \\__ \\/ __ \\/ __ `/ //_/ _ \\\n");
	printf(" ___/ / / / / /_/ / ,< /  __/\n");
	printf("/____/_/ /_/\\__,_/_/|_|\\___/ \n");
	for (int i = 0; i != 34; i++) {
		wprintf(L"%lc",205);
	}
	printf("\n");
	printf("You are Q\n");
	printf("You move with the WASD keys.\n");
	printf("Get the fruit. (@)\n");
	printf("As you get fruits, you'll get bigger.\n");
	printf("If you touch your tail or the walls, you lose.\n");
	printf("Have fun!\n");
	for (int i = 0; i != 34; i++) {
		wprintf(L"%lc", 205);
	}
	printf("\n");
	system("pause");
	system("cls");
}

//Places random fruit when obtained
void placeFruit(Fruit * fruit) {
	if (fruit->flags & isObtained) {
		fruit->flags &= ~(isObtained);
		srand(time(0));
		fruit->x = rand() % MAX_X;
		fruit->y = rand() % MAX_Y;
		if (fruit->x < 1) {
			fruit->x = 1;
		}
		if (fruit->y < 1) {
			fruit->y = 1;
		}
		if (fruit->x > MAX_X-1) {
			fruit->x = MAX_X-1;
		}
		if (fruit->y > MAX_Y-1) {
			fruit->y = MAX_Y-1;
		}
	}
}

//For movements
void move(Snek * player, unsigned char direction, unsigned int score) {
	
	
	//Tail
	for (unsigned int i = score; i > 0; i--) {
		int prevX = player->TailX[i];
		int prevY = player->TailY[i];
		player->TailX[i] = player->x;
		player->TailY[i] = player->y;
		player->TailX[i + 1] = prevX;
		player->TailY[i + 1] = prevY;
	}
	

	//Move according to directions
	if (direction == UP) {
		player->y--;
	}
	else if (direction == DOWN) {
		player->y++;
	}
	else if (direction == LEFT) {
		player->x--;
	}
	else if (direction == RIGHT) {
		player->x++;
	}
	
	//If touched wall
	if (player->x < 1 || player->y < 1 || player->x >= MAX_X-1 || player->y >= MAX_Y-1) {
		player->flags |= isStillPlaying;
	}
	//If touched his tail
	for (unsigned int i = 0; i < score; i++) {
		if ((player->x == player->TailX[i] && player->y == player->TailY[i])) {
			player->flags |= isStillPlaying;
		}
	}
}

void printBoard(Snek snek, Fruit fruit, unsigned int score, unsigned int direction) {
	system("cls");
	int kStarts0 = 0;
	for (int j = 0; j <= MAX_Y; j++) {
		for (int i = 0; i != MAX_X; i++) {	

			//Walls
			if (j == 0) {
				wprintf(L"%lc",220);
			}
			else if (j == MAX_Y) {
				wprintf(L"%lc",223);
			}
			else if (i == 0 || i == MAX_X - 1) {
				wprintf(L"%lc",219);
			}
			
			//Fruit
			else if (i == fruit.x && j == fruit.y) {
				printf("@");
			}

			//Head
			else if (i == snek.x && j == snek.y) {
				printf("Q");
			}
			
			//Spaces
			else {
				//Tail
				for (int k = 0; k <= score; k++) {
					if (i == snek.TailX[k] && j == snek.TailY[k]) {
						printf("o");
						goto endCycle;
					}
				}
				printf(" ");
			}
		endCycle:{}
		}
		printf("\n");
	}
	//Score meter
	printf("Score: %d", score);
}

int main() {
	//Setup
	Snek snek{
		0,
		3,3,
		0,0
	};
	Fruit fruit{
		0,
		1,2
	};
	unsigned int score = 0;
	unsigned char direction = RIGHT;
	unsigned int sleepIncrease = 275;

	//Instructions
	printInstructions();

		//Initialization
	fruit.flags |= isObtained;
	placeFruit(&fruit);

	while ((snek.flags & isStillPlaying) == 0) {
		//Game procedures
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				if (direction != DOWN) {
					direction = UP;
				}
				break;
			case 's':
				if (direction != UP) {
					direction = DOWN;
				}
				break;
			case 'a':
				if (direction != RIGHT) {
					direction = LEFT;
				}
				break;
			case 'd':
				if (direction != LEFT) {
					direction = RIGHT;
				}
				break;
			}
		}
		move(&snek,direction,score);
		if (snek.x == fruit.x && snek.y == fruit.y) {
			score++;
			sleepIncrease -= 5;
			fruit.flags |= isObtained;
			placeFruit(&fruit);
		}
		printBoard(snek, fruit, score, direction);
		Sleep(sleepIncrease);
	}

	//Ending message
	printf("\nGame Over! Better luck next time!\n");
	system("pause");
	return 0;
}