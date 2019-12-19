#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define MAX_X 30
#define MAX_Y 13

enum Flags {
	isPlaying = 1 << 0,
	hasStarted = 1 << 1,
	multiPlayerMode = 1 << 2,
	VerDirection = 1 << 3, //1: Superior / 0: Inferior
	HorDirection = 1 << 4, //1: Right / 0: Left
	hasGoaled = 1 << 5,
	hasHit = 1 << 6,
};
enum Angles {
	Low, //30º
	Mid, //45º
	High, //60º
	Hor
};
enum Difficulty {
	Easy, Hard
};

struct Bar {
	int x[5], y[5];
	unsigned char flags;
	int score;
};

struct Ball {
	int x, y;
	unsigned char flags;
};

int Instructions() {
	printf("  __  __ _       _   _____                  \n");
	printf(" |  \\/  (_)     (_) |  __ \\                 \n");
	wprintf(L" | \\  / |_ _ __  _  | |__)|___  _ __   __ _ %lc     ___   __  \n", 184);
	printf(" | |\\/| | | '_ \\| | |  ___/ _ \\| '_ \\ / _` | __ _|_  ) /  \\ \n");
	printf(" | |  | | | | | | | | |  | (_) | | | | (_| | \\ V // / | () |\n");
	printf(" |_|  |_|_|_| |_|_| |_|   \\___/|_| |_|\\__, |  \\_//___(_)__/ \n");
	printf("                                       __/ |\n");
	printf("                                      |___/ \n");


	for (int i = 0; i != 5; i++) {
		printf(">");
		printf("<");
	}
	printf("\nThe game you know and love, now available on machine language!\n");
	printf("With singleplayer and multiplayer modes!\n");
	for (int i = 0; i != 5; i++) {
		printf(">");
		printf("<");
	}
	printf("\nControls:\n\n");
	wprintf(L"W & S: Move Player 1's bar (%lc)\n", 186);
	wprintf(L"O & L: Move Player 2's bar (%lc)\n\n", 186);
	printf("Have fun!\n\n");
	system("pause");

	printf("\nSelect mode:\n");
	printf("0. Multiplayer mode.\n");
	printf("1. VS. AI (Coming Soon...)\n");
	int a;
	scanf("%d", &a);
	return a;
}

void moveBall(Ball* ball, Bar bar1, Bar bar2, int angles) {
	//Goal State
	if ((ball->flags & hasGoaled) != 0 || (ball->flags & hasStarted) != 0) {
		ball->flags &= ~(hasGoaled);
		ball->flags &= ~(hasStarted);
		ball->x = MAX_X / 2;
		ball->y = MAX_Y / 2;
		ball->flags |= HorDirection;
		ball->flags |= VerDirection;
		goto endCycle;
	}

	//Collisions Bars
	for (int i = 0; i != 3; i++) {
		if (ball->y == bar1.y[i] && ball->x <= 2) {
			ball->x = 2;
			ball->flags |= HorDirection;
			ball->flags |= hasHit;
		}
		else if (ball->y == bar2.y[i] && ball->x >= MAX_X - 2) {
			ball->x = MAX_X - 2;
			ball->flags &= ~(HorDirection);
			ball->flags |= hasHit;
		}
	}

	//Movement
	//VerDirection 1: Superior / 0: Inferior
	//HorDirection 1: Right / 0: Left
	if (angles == Low) {
		if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) != 0) {
			ball->x += 2;
			ball->y--;
		}
		else if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) == 0) {
			ball->x -= 2;
			ball->y--;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) == 0) {
			ball->x -= 2;
			ball->y++;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) != 0) {
			ball->x += 2;
			ball->y++;
		}
	}
	else if (angles == Mid) {
		if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) != 0) {
			ball->x++;
			ball->y--;
		}
		else if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) == 0) {
			ball->x--;
			ball->y--;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) == 0) {
			ball->x--;
			ball->y++;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) != 0) {
			ball->x++;
			ball->y++;
		}
	}
	else if (angles == High) {
		if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) != 0) {
			ball->x++;
			ball->y -= 2;
		}
		else if ((ball->flags & VerDirection) != 0 && (ball->flags & HorDirection) == 0) {
			ball->x--;
			ball->y -= 2;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) == 0) {
			ball->x--;
			ball->y += 2;
		}
		else if ((ball->flags & VerDirection) == 0 && (ball->flags & HorDirection) != 0) {
			ball->x++;
			ball->y += 2;
		}
	}
	else if (angles == Hor) {
		if ((ball->flags & HorDirection) != 0) {
			ball->x += 2;
		}
		else if ((ball->flags & HorDirection) == 0) {
			ball->x -= 2;
		}
	}
	
	//Collision Walls
	if (ball->y <= 1) {
		ball->y = 1;
		ball->flags &= ~(VerDirection);
	}
	else if (ball->y >= MAX_Y - 1) {
		ball->y = MAX_Y - 1;
		ball->flags |= VerDirection;
	}

endCycle: {}
}

void draw(Ball ball, Bar p1, Bar p2) {
	system("cls");
	for (int j = 0; j <= MAX_Y; j++) {
		for (int i = 0; i <= MAX_X; i++) {
			if (j == 0 || j == MAX_Y) {
				wprintf(L"%lc", 177);
			}
			else if (i == 0 || i == MAX_X) {
				wprintf(L"%lc", 176);
			}
			else if (i == ball.x && j == ball.y) {
				wprintf(L"%lc", 184);
			}
			else if (i == MAX_X / 2) {
				printf(":");
			}
			else {
				for (int k = 0; k != 5; k++) {
					if ((i == p1.x[k] && j == p1.y[k]) || (i == p2.x[k] && j == p2.y[k])) {
						wprintf(L"%lc", 186);
						goto endCycle;
					}
				}
				printf(" ");
			}
		endCycle: {}
		}
		printf("\n");
	}
	printf("Score 1: %d", p1.score);
	for (int i = 0; i != ((MAX_X)-19); i++) {
		printf(" ");
	}
	printf("Score 2: %d", p2.score);

	if ((ball.flags & hasGoaled) != 0) {
		if (ball.x == 0) {
			printf("\nPlayer 2 has scored a point!\n\n");
		}
		else {
			printf("\nPlayer 1 has scored a point!\n\n");
		}
		system("pause");
	}
}

void moveBars(Ball ball, Bar* p1, Bar* p2, int difficulty) {
	//Reset positions
	if ((ball.flags & hasGoaled) != 0) {
		p1->y[0] = (MAX_Y / 2) - 1;
		p1->y[1] = (MAX_Y / 2);
		p1->y[2] = (MAX_Y / 2) + 1;
		p2->y[0] = (MAX_Y / 2) - 1;
		p2->y[1] = (MAX_Y / 2);
		p2->y[2] = (MAX_Y / 2) + 1;
	}

	if ((ball.flags & multiPlayerMode) != 0) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				if (p1->y[0] > 1) {
					for (int i = 0; i != 3; i++) {
						p1->y[i]--;
					}
				}
				break;
			case 's':
				if (p1->y[2] < MAX_Y - 1) {
					for (int i = 0; i != 5; i++) {
						p1->y[i]++;
					}
				}
				break;
			case 'o':
				if (p2->y[0] > 1) {
					for (int i = 0; i != 3; i++) {
						p2->y[i]--;
					}
				}
				break;
			case 'l':
				if (p2->y[2] < MAX_Y - 1) {
					for (int i = 0; i != 5; i++) {
						p2->y[i]++;
					}
				}
				break;
			}
		}
	}
	else {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				if (p1->y[0] > 1) {
					for (int i = 0; i != 3; i++) {
						p1->y[i]--;
					}
				}
				break;
			case 's':
				if (p1->y[2] < MAX_Y - 1) {
					for (int i = 0; i != 5; i++) {
						p1->y[i]++;
					}
				}
				break;
			}
		}

		//IA
		//1:Moves Up,0:Moves Down
		if (difficulty == Hard) {
			if (ball.y < p2->y[1]) {
				for (int i = 0; i != 3; i++) {
					p2->y[i]--;
				}
			}
			else if (ball.y > p2->y[1]) {
				for (int i = 0; i != 3; i++) {
					p2->y[i]++;
				}
			}
		}
		else if (difficulty == Easy) {
			if ((p2->flags & VerDirection) != 0) {
				for (int i = 0; i != 3; i++) {
					p2->y[i]--;
				}
			}
			else if ((p2->flags & VerDirection) == 0) {
				for (int i = 0; i != 3; i++) {
					p2->y[i]++;
				}
			}
		}

		//Collision with wall
		if (p2->y[0] < 1) {
			p2->flags &= ~(VerDirection);
			p2->y[0] = 2;
			for (int i = 1; i != 3; i++) {
				p2->y[i] = p2->y[i - 1] + 1;
			}
		}
		else if (p2->y[2] > MAX_Y - 1) {
			p2->flags |= VerDirection;
			p2->y[2] = MAX_Y - 1;
			for (int i = 1; i != -1; i--) {
				p2->y[i] = p2->y[i + 1] - 1;
			}
		}
	}
}

int main() {
	//Setup
	Ball ball{
		MAX_X / 2,MAX_Y / 2,
		0
	};
	Bar p1{
		{1,1,1},{(MAX_Y / 2) - 1,(MAX_Y / 2),(MAX_Y / 2) + 1,},
		0,0,
	};
	Bar p2{
		{ MAX_X - 1 , MAX_X - 1 , MAX_X - 1},{(MAX_Y / 2) - 1,(MAX_Y / 2),(MAX_Y / 2) + 1},
		0,0,
	};
	int gamemode = Instructions();
	p2.flags |= VerDirection;
	int difficulty = 0;//For difficulty

	ball.flags |= isPlaying;
	if (gamemode == 0) {
		ball.flags |= multiPlayerMode;
	}
	else if (gamemode == 1) {
		printf("\nSelect difficulty:\n");
		printf("0.Easy mode\n");
		printf("1.Hard mode\n");
		scanf("%d", &difficulty);
	}

	//Initial Ball movement (45º)
	int angles = Mid;
	ball.flags |= VerDirection;
	ball.flags |= HorDirection;
	ball.flags |= hasStarted;

	while ((ball.flags & isPlaying) != 0) {
		draw(ball, p1, p2);
		moveBars(ball, &p1, &p2, difficulty);
		moveBall(&ball, p1, p2, angles);
		if ((ball.flags & hasHit) != 0) {
			ball.flags &= ~(hasHit);
			srand(time(NULL));
			angles = rand() % 4;
		}
		if (ball.x <= 0) {
			p2.score++;
			ball.flags |= hasGoaled;
			angles = rand() % 4;
		}
		else if (ball.x >= MAX_X) {
			p1.score++;
			ball.flags |= hasGoaled;
			angles = rand() % 4;
		}
		Sleep(200);
	}

	system("pause");
	return 0;
}