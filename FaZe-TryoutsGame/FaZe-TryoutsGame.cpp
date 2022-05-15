#include <iostream>
#include <iomanip>
#include <thread>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 30;

const int xStartPosition = 50;

int colorSelectionVar;

string gridTop[1] = { "*" };
string gridJungle[2] = { "*", "*" };
string gridMid[3] = { "*", "*", "*" };
string gridBot[4] = { "*", "*", "*" , "*" };
string gridSupp[5] = { "*", "*", "*" , "*", "*" };

int topCard1 = rand() % 2;
int topCard2 = rand() % 2;
int topCard3 = rand() % 2;
int topCard4 = rand() % 2;
int topCard5 = rand() % 2;
int topCard6 = rand() % 2;

int bottomCard1 = rand() % 2;
int bottomCard2 = rand() % 2;
int bottomCard3 = rand() % 2;
int bottomCard4 = rand() % 2;
int bottomCard5 = rand() % 2;
int bottomCard6 = rand() % 2;

string andCard0[8] = { "0[AND]" , "0[AND]" , "0[AND]" ,"0[AND]" , "0[AND]" , "0[AND]" , "0[AND]", "0[AND]" };
int andCard0Counter = 0;
string andCard1[8] = { "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" };
int andCard1Counter = 0;

string orCard0[8] = { "0[OR]" , "0[OR]" , "0[OR]" ,"0[OR]" , "0[OR]" , "0[OR]" , "0[OR]", "0[OR]" };
int orCard0Counter = 0;
string orcard1[8] = { "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" };
int orCard1Counter = 0;

string xorCard0[8] = { "0[XOR]" , "0[XOR]" , "0[XOR]" ,"0[XOR]" , "0[XOR]" , "0[XOR]" , "0[XOR]", "0[XOR]" };
int xorCard0Counter = 0;
string xorcard1[8] = { "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" };
int xorCard1Counter = 0;

string cards[48] =
{
	"0[AND]" , "0[AND]" , "0[AND]" ,"0[AND]" , "0[AND]" , "0[AND]" , "0[AND]", "0[AND]" ,
	"1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" , "1[AND]" ,
	"0[OR]" , "0[OR]" , "0[OR]" ,"0[OR]" , "0[OR]" , "0[OR]" , "0[OR]", "0[OR]" ,
	"1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" , "1[OR]" ,
	"0[XOR]" , "0[XOR]" , "0[XOR]" ,"0[XOR]" , "0[XOR]" , "0[XOR]" , "0[XOR]", "0[XOR]" ,
	"1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]" , "1[XOR]"
};

string yourCards[5];
int randomCard = 0;

int cardSum = 0;


enum
{
	BLACK = 0,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
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
	for (int i = 0; i < 5; i++)
	{
		cardSum++;
		randomCard = rand() % 48;

		yourCards[i] = cards[randomCard];
	}

	if (topCard1 == 0)
		bottomCard1 = 1;
	else if (topCard1 == 1)
		bottomCard1 = 0;

	if (topCard2 == 0)
		bottomCard2 = 1;
	else if (topCard2 == 1)
		bottomCard2 = 0;

	if (topCard3 == 0)
		bottomCard3 = 1;
	else if (topCard3 == 1)
		bottomCard3 = 0;

	if (topCard4 == 0)
		bottomCard4 = 1;
	else if (topCard4 == 1)
		bottomCard4 = 0;

	if (topCard5 == 0)
		bottomCard5 = 1;
	else if (topCard5 == 1)
		bottomCard5 = 0;

	if (topCard6 == 0)
		bottomCard6 = 1;
	else if (topCard6 == 1)
		bottomCard6 = 0;

	gotoxy(34, 10);

	for (int i = 0; i < 5; i++)
		cout << gridSupp[i] << setw(8);

	gotoxy(31, 8);

	for (int i = 0; i < 4; i++)
		cout << gridBot[i] << setw(8);

	gotoxy(35, 6);

	for (int i = 0; i < 3; i++)
		cout << gridMid[i] << setw(8);

	gotoxy(39, 4);

	for (int i = 0; i < 2; i++)
		cout << gridJungle[i] << setw(8);

	gotoxy(43, 2);

	cout << gridTop[0];

	gotoxy(30, 12);
	cout << topCard1 << setw(8) << topCard2 << setw(8) << topCard3 << setw(8) << topCard4 << setw(8) << topCard5 << setw(8) << topCard6 << endl;
	gotoxy(30, 13);
	cout << bottomCard1 << setw(8) << bottomCard2 << setw(8) << bottomCard3 << setw(8) << bottomCard4 << setw(8) << bottomCard5 << setw(8) << bottomCard6 << endl;

	gotoxy(34, 15);

	for (int i = 0; i < 5; i++)
		cout << gridSupp[i] << setw(8);

	gotoxy(31, 17);

	for (int i = 0; i < 4; i++)
		cout << gridBot[i] << setw(8);

	gotoxy(35, 19);

	for (int i = 0; i < 3; i++)
		cout << gridMid[i] << setw(8);

	gotoxy(39, 21);

	for (int i = 0; i < 2; i++)
		cout << gridJungle[i] << setw(8);

	gotoxy(43, 23);

	cout << gridTop[0] << endl;

	cout << "Your cards: " << endl;
	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		if (yourCards[i] == "0[AND]")
			andCard0Counter++;
		else if (yourCards[i] == "1[AND]")
			andCard1Counter++;
		else if (yourCards[i] == "0[OR]")
			orCard0Counter++;
		else if (yourCards[i] == "1[OR]")
			orCard1Counter++;
		else if (yourCards[i] == "0[XOR]")
			xorCard0Counter++;
		else if (yourCards[i] == "1[XOR]")
			xorCard1Counter++;
		cout << yourCards[i] << " ";
	}

	cout << endl;
	cout << endl;

	cout << "----------------" << endl;
	cout << "|" << "AND-0 Cards: " << andCard0Counter << "|" << endl;
	cout << "----------------" << endl;
	cout << "|" << "AND-1 Cards: " << andCard1Counter << "|" << endl;
	cout << "----------------" << endl;
	cout << "|" << "OR-0 Cards: " << orCard0Counter << " |" << endl;
	cout << "----------------" << endl;
	cout << "|" << "OR-1 Cards: " << orCard1Counter << " |" << endl;
	cout << "----------------" << endl;
	cout << "|" << "XOR-0 Cards: " << xorCard0Counter << "|" << endl;
	cout << "----------------" << endl;
	cout << "|" << "XOR-1 Cards: " << xorCard1Counter << "|" << endl;
	cout << "----------------" << endl;

	int cardPlace;
	cout << "Choose a number from 1 to " << cardSum << ":";
	cin >> cardPlace;

	while (cardPlace < 1 || cardPlace > cardSum)
	{
		cin.ignore();
		cout << "Invalid number. Please choose from 1 to " << cardSum << ":";
		cin >> cardPlace;
	}

	string chosenCard;
	cout << "Choose a card(Please write the whole name. Example: 0[OR])";
	cin >> chosenCard;

	while (chosenCard != "0[AND]" && chosenCard != "1[AND]" && chosenCard != "0[OR]" && chosenCard != "1[OR]" && chosenCard != "0[XOR]" && chosenCard != "1[XOR]")
	{
		cin.ignore();
		cout << "Invalid number. Please check if you've written the name of the card correctly!" << endl;
		cout << "Choose a card(Please write the whole name. Example: 0[OR])";
		cin >> chosenCard;
	}

}

int main()
{
	srand(time(0));

	mainMenu();
}