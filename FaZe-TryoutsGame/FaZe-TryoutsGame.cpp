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

int main()
{
	mainMenu();
	return 0;
}