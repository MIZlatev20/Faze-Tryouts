#include <iostream>
#include <thread>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

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

int main()
{
	mainMenu();
	return 0;
}