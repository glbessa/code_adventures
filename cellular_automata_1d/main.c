// https://mathworld.wolfram.com/ElementaryCellularAutomaton.html
// https://www.youtube.com/watch?v=DKGodqDs9sA
// https://www.wolframscience.com/nks/
// https://natureofcode.com/book/chapter-7-cellular-automata/
// https://mathworld.wolfram.com/
// http://atlas.wolfram.com/
// https://mathworld.wolfram.com/TotalisticCellularAutomaton.html
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define LENGTH 25
#define ITERATIONS 1000000

#define WHITE_TILE "\x1b[97m\x1b[107m"
#define GRAY_TILE "\x1b[90;100m"
#define RESET_TILE "\x1b[0m"
#define INVISIBLE_CURSOR "\x1b[?25l"

#define SLEEP_TIME 150000

void runCellAutomata(int *cells, int *newCells, int length, int sleepTime, int iterations);
void runComplexCellAutomata(int *cells, int *newCells, int length, int sleepTime, int iterations);
void randomInitialize(int *cells, int length, int max);
int *generate(int *cells, int length);
int *generateComplex(int *cells, int length);
int rules(int a, int b, int c);
int complexRules(int a, int b, int c);
void printAutomata(int *cells, int length, char *msg);
void printComplexAutomata(int *cells, int length, char *msg);
int generateRandomInt(int min, int max);

int main(char *args[])
{
	srand(time(NULL));
	int *cells = (int *) malloc(sizeof(int) * LENGTH);
	int *newCells;

	// rule 90
	cells[19] = 1;
	// rule 110
	//cells[LENGTH - 1] = 1;
	// rule 184 122 1041
	//randomInitialize(cells, LENGTH, 1);

	printf("%s", INVISIBLE_CURSOR);

	//runComplexCellAutomata(cells, newCells, LENGTH, SLEEP_TIME, ITERATIONS);
	runCellAutomata(cells, newCells, LENGTH, SLEEP_TIME, ITERATIONS);

	return 0;
}

void runCellAutomata(int *cells, int *newCells, int length, int sleepTime, int iterations)
{
	printAutomata(cells, length, "");
	usleep(sleepTime);
	for (int i = 0; i < iterations; i++)
	{
		newCells = generate(cells, length);
		printAutomata(newCells, length, "");
		cells = newCells;
		usleep(sleepTime);
	}
}

void runComplexCellAutomata(int *cells, int *newCells, int length, int sleepTime, int iterations)
{
	printComplexAutomata(cells, length, "");
	usleep(sleepTime);
	for (int i = 0; i < iterations; i++)
	{
		newCells = generateComplex(cells, length);
		printComplexAutomata(newCells, length, "");
		cells = newCells;
		usleep(sleepTime);
	}
}

void randomInitialize(int *cells, int length, int max)
{
	for(int i = 0; i < length; i++)
	{
		cells[i] = generateRandomInt(0, max);
	}
}

int *generate(int *cells, int length)
{
	int *newCells = (int *) malloc(sizeof(int) * length);
	for (int i = 1; i < length - 1; i++)
	{
		newCells[i] = rules(cells[i-1], cells[i], cells[i+1]);
	}
	return newCells;
}

int *generateComplex(int *cells, int length)
{
	int *newCells = (int *) malloc(sizeof(int) * length);
	for (int i = 1; i < length - 1; i++)
	{
		newCells[i] = complexRules(cells[i-1], cells[i], cells[i+1]);
	}
	return newCells;
}

int rules(int a, int b, int c)
{
	// 000 001 010 011 100 101 110 111
	// rule 90
	int stateRules[] = {0, 1, 0, 1, 1, 0, 1, 0};
	// rule 184
	//int stateRules[] = {0, 0, 0, 1, 1, 1, 0, 1};
	// rule 110
	//int stateRules[] = {0, 1, 1, 1, 0, 1, 1, 0};
	// rule 122
	//int stateRules[] = {0, 1, 0, 1, 1, 1, 1, 0};

	char str[4];
	sprintf(str, "%i%i%i", a, b, c);

	int cod = strtol(str, NULL, 2);
	int newState = stateRules[cod];

	return newState;
}

// 3-color totalistic celular automata
// https://mathworld.wolfram.com/TotalisticCellularAutomaton.html
// base 3
int complexRules(int a, int b, int c)
{
	int sum = (a + b + c);

	// 0 1 2 3 4 5 6
	// rule 1041
	int states[7] = {0, 2, 1, 2, 0, 1, 1};

	return states[sum];
}

void printAutomata(int *cells, int length, char *msg)
{
	printf("%s", msg);
	for (int i = 0; i < length; i++)
	{
		if (cells[i] == 0)
			printf("  ");
		else
			printf("%s %s ", WHITE_TILE, RESET_TILE);
	}
	printf("\n");
}

void printComplexAutomata(int *cells, int length, char *msg)
{
	printf("%s", msg);
	for (int i = 0; i < length; i++)
	{
		switch(cells[i])
		{
			case 0:
				printf("%s %s ", WHITE_TILE, RESET_TILE);
				break;
			case 1:
				printf("%s %s ", GRAY_TILE, RESET_TILE);
				break;
			case 2:
				printf("  ");
				break;
		}
	}
	printf("\n");
}

int generateRandomInt(int min, int max)
{
	return (rand() % (max+1)) + min;
}