#include <iostream>
#include <iomanip>
#include <thread>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

int nFieldWidth = 12;
int nFieldHeight = 18;

int nScreenWidth = 120;
int nScreenHeight = 30;

int nCurrentY = 0;

const int xStartPosition = 50;

wchar_t* pField = nullptr;

int colorSelectionVar;
int tempScore = 0;


enum
{
	BLACK = 0,
	DARKBLUE = FOREGROUND_BLUE,
	DARKGREEN = FOREGROUND_GREEN,
	DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DARKRED = FOREGROUND_RED,
	DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	GRAY = FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

WORD displayColor[] = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };

bool colorSelection(WORD newColor)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut != INVALID_HANDLE_VALUE)
		return SetConsoleTextAttribute(hStdOut, newColor);

	return false;
}

// Coordinates of X and Y
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Logo()
{
	colorSelection(YELLOW);
	cout << R"(
		  
	     .------..------..------..------.     .------..------..------..------..------..------..------.
	     |F.--. ||A.--. ||Z.--. ||E.--. |.-.  |T.--. ||R.--. ||Y.--. ||O.--. ||U.--. ||T.--. ||S.--. |
	     | :(): || (\/) || :(): || (\/) ((5)) | :/\: || :(): || (\/) || :/\: || (\/) || :/\: || :/\: |
	     | ()() || :\/: || ()() || :\/: |'-.-.| (__) || ()() || :\/: || :\/: || :\/: || (__) || :\/: |
	     | '--'F|| '--'A|| '--'Z|| '--'E| ((1)) '--'T|| '--'R|| '--'Y|| '--'O|| '--'U|| '--'T|| '--'S|
	     `------'`------'`------'`------'  '-'`------'`------'`------'`------'`------'`------'`------'
                                                                                    
)" << '\n';
}

void helpLogo()
{
	colorSelection(YELLOW);
	cout << R"(
					.------..------..------..------.
					|H.--. ||E.--. ||L.--. ||P.--. |
					| :/\: || (\/) || :/\: || :/\: |
					| (__) || :\/: || (__) || (__) |
					| '--'H|| '--'E|| '--'L|| '--'P|
					`------'`------'`------'`------'
                                                                                                                                                                 
)" << '\n';
}

void rulesLogo()
{
	colorSelection(YELLOW);
	cout << R"(
					.------..------..------..------..------.
					|R.--. ||U.--. ||L.--. ||E.--. ||S.--. |
					| :(): || (\/) || :/\: || (\/) || :/\: |
					| ()() || :\/: || (__) || :\/: || :\/: |
					| '--'R|| '--'U|| '--'L|| '--'E|| '--'S|
					`------'`------'`------'`------'`------' 
                                                                                                                
)" << '\n';
}

void mainMenu();
void rulesMenu();
void helpMenu();
void game();

void mainMenu()
{
	Logo();

	int counter = 1;
	char key;

	for (;;)
	{
		if (counter >= 1 && counter <= 4)
			displayColor[counter - 1] = RED;

		gotoxy(xStartPosition, 9);
		colorSelection(displayColor[0]);
		cout << "1. Start";

		gotoxy(xStartPosition, 10);
		colorSelection(displayColor[1]);
		cout << "2. Help";

		gotoxy(xStartPosition, 11);
		colorSelection(displayColor[2]);
		cout << "3. Rules";

		gotoxy(xStartPosition, 12);
		colorSelection(displayColor[3]);
		cout << "4. Exit";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4)) // 72 - up arrow (keyboard)
			counter--;
		if (key == 80 && (counter >= 1 && counter <= 3)) // 80 - down arrow (keyboard)
			counter++;

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			for (int i = 0; i < 4; i++)
				displayColor[i] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				game();
				break;
			}
			else if (counter == 2)
			{
				helpMenu();
				break;
			}
			else if (counter == 3)
			{
				rulesMenu();
				break;
			}
			else if (counter == 4)
			{
				exit(EXIT_SUCCESS);
			}
		}
		for (int i = 0; i < 4; i++)
			displayColor[i] = WHITE;
	}
}

void helpMenu()
{
	helpLogo();

	int counter = 1;
	char key;

	for (int i = 0;;)
	{
		if (counter == 1) { displayColor[0] = RED; }

		colorSelection(GREEN);
		gotoxy(25, 9);
		cout << "Rules:" << endl;
		gotoxy(25, 10);
		cout << "Rules here" << endl;
		gotoxy(25, 11);
		cout << "rules here" << endl;
		gotoxy(25, 12);
		cout << "rules here " << endl;
		gotoxy(25, 13);
		cout << "rules here!";
		gotoxy(25, 14);
		cout << "Escape button: Exit";

		gotoxy(xStartPosition, 15);
		colorSelection(displayColor[0]);
		cout << "Go Back";

		key = _getch();

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			displayColor[0] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				mainMenu();
				break;
			}
		}
		displayColor[0] = WHITE;
	}
}

void rulesMenu()
{
	rulesLogo();

	int counter = 1;
	char key;

	for (int i = 0;;)
	{
		if (counter == 1) { displayColor[0] = RED; }

		colorSelection(GREEN);
		gotoxy(25, 9);
		cout << "rules here" << endl;
		gotoxy(25, 10);
		cout << "rules here" << endl;
		gotoxy(25, 11);
		cout << "rules here" << endl;
		gotoxy(25, 12);
		cout << "rules here " << endl;
		gotoxy(25, 13);
		cout << "rules here";
		gotoxy(25, 14);
		cout << "Escape button: Exit";

		gotoxy(xStartPosition, 15);
		colorSelection(displayColor[0]);
		cout << "Go Back";

		key = _getch();

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			displayColor[0] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				mainMenu();
				break;
			}
		}
		displayColor[0] = WHITE;
	}
}

void game()
{
	string gridTop[1] = { "*" };
	string gridJungle[2] = { "*", "*" };
	string gridMid[3] = { "*", "*", "*" };
	string gridBot[4] = { "*", "*", "*" , "*" };

	srand(time(0));

	int topcard1 = rand() % 2;
	int topcard2 = rand() % 2;
	int topcard3 = rand() % 2;
	int topcard4 = rand() % 2;
	int topcard5 = rand() % 2;

	int bottomcard1 = rand() % 2;
	int bottomcard2 = rand() % 2;
	int bottomcard3 = rand() % 2;
	int bottomcard4 = rand() % 2;
	int bottomcard5 = rand() % 2;

	int andcard0[8] = { 01 , 01 , 01 , 01 , 01 , 01 , 01, 01 };
	int andcard0counter = 0;
	int andcard1[8] = { 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 };
	int andcard1counter = 0;

	int orcard0[8] = { 02 , 02 , 02 , 02 , 02 , 02 , 02 , 02 };
	int orcard0counter = 0;
	int orcard1[8] = { 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 };
	int orcard1counter = 0;

	int xorcard0[8] = { 03 , 03 , 03 , 03 , 03 , 03 , 03 , 03 };
	int xorcard0counter = 0;
	int xorcard1[8] = { 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 };
	int xorcard1counter = 0;

	int cards[48] =
	{
		01 , 01 , 01 , 01 , 01 , 01 , 01 , 01 ,
		11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 ,
		02 , 02 , 02 , 02 , 02 , 02 , 02 , 02 ,
		12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 ,
		03 , 03 , 03 , 03 , 03 , 03 , 03 , 03 ,
		13 , 13 , 13 , 13 , 13 , 13 , 13 , 13
	};

	int yourcards[5];

	if (topcard1 == 0)
	{
		bottomcard1 = 1;
	}
	else if (topcard1 == 1)
	{
		bottomcard1 = 0;
	}

	if (topcard2 == 0)
	{
		bottomcard2 = 1;
	}
	else if (topcard2 == 1)
	{
		bottomcard2 = 0;
	}

	if (topcard3 == 0)
	{
		bottomcard3 = 1;
	}
	else if (topcard3 == 1)
	{
		bottomcard3 = 0;
	}

	if (topcard4 == 0)
	{
		bottomcard4 = 1;
	}
	else if (topcard4 == 1)
	{
		bottomcard4 = 0;
	}

	if (topcard5 == 0)
	{
		bottomcard5 = 1;
	}
	else if (topcard5 == 1)
	{
		bottomcard5 = 0;
	}

	gotoxy(33, 7);

	for (int i = 0; i < 4; i++)
	{
		cout << gridBot[i] << setw(10);
	}

	gotoxy(29, 5);

	for (int i = 0; i < 3; i++)
	{
		cout << gridMid[i] << setw(10);
	}

	gotoxy(34, 3);

	for (int i = 0; i < 2; i++)
	{
		cout << gridJungle[i] << setw(10);
	}

	gotoxy(39, 1);

	cout << gridTop[0];

	gotoxy(30, 8);
	cout << topcard1 << setw(9) << topcard2 << setw(9) << topcard3 << setw(9) << topcard4 << setw(9) << topcard5 << endl;
	gotoxy(30, 9);
	cout << bottomcard1 << setw(9) << bottomcard2 << setw(9) << bottomcard3 << setw(9) << bottomcard4 << setw(9) << bottomcard5 << endl;

	gotoxy(33, 11);

	for (int i = 0; i < 4; i++)
	{
		cout << gridBot[i] << setw(10);
	}

	gotoxy(29, 13);

	for (int i = 0; i < 3; i++)
	{
		cout << gridMid[i] << setw(10);
	}

	gotoxy(34, 15);

	for (int i = 0; i < 2; i++)
	{
		cout << gridJungle[i] << setw(10);
	}

	gotoxy(39, 17);

	cout << gridTop[0];
}

int main()
{
	mainMenu();
}