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

// Grid
string lRowGrid[1] = { "*" };
string foRowGrid[2] = { "*", "*" };
string tRowGrid[3] = { "*", "*", "*" };
string sRowGrid[4] = { "*", "*", "*" , "*" };
string fRowGrid[5] = { "*", "*", "*" , "*", "*" };

// Initializing the initial cards
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

// Initializing the different types of cards
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

// Initializing the card deck
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
		cout << "Help:" << endl;
		gotoxy(25, 10);
		cout << "The game is not time based so you can take your time choosing what card to play. " << endl;
		gotoxy(25, 11);
		cout << "Each card has its own rules so don't worry if you are confused at the start. " << endl;
		gotoxy(25, 12);
		cout << "You don't have to always play a card you can also discard a card or draw a card." << endl;

		gotoxy(xStartPosition, 14);
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
		cout << "Rule 1: The deck of cards must be shuffled." << endl;
		gotoxy(25, 10);
		cout << "Rule 2: You must only place the correct card corresponding to its place." << endl;
		gotoxy(25, 11);
		cout << "Rule 3: B00le0 puts your Boolean algebra skills to use as you try to" << endl;
		gotoxy(25, 12);
		cout << "        resolve your inputs to the correct single digit before your opponent does." << endl;
		gotoxy(25, 13);
		cout << "Rule 4: Place gates on two inputs, creating a new output, and keep" << endl;
		gotoxy(25, 14);
		cout << "        building until you create the one, final digit that you need to complete the pyramid." << endl;
		gotoxy(25, 15);
		cout << "Rule 5: The game starts by placing the Initial Binary cards in a row between the players." << endl;
		gotoxy(25, 16);
		cout << "Rule 6: Take turns playing a card or either discarding a card or draw a card." << endl;

		gotoxy(xStartPosition, 18);
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

	// Making the grid
	gotoxy(34, 10);

	for (int i = 0; i < 5; i++)
		cout << fRowGrid[i] << setw(8);

	gotoxy(31, 8);

	for (int i = 0; i < 4; i++)
		cout << sRowGrid[i] << setw(8);

	gotoxy(35, 6);

	for (int i = 0; i < 3; i++)
		cout << tRowGrid[i] << setw(8);

	gotoxy(39, 4);

	for (int i = 0; i < 2; i++)
		cout << foRowGrid[i] << setw(8);

	gotoxy(43, 2);

	cout << lRowGrid[0];

	gotoxy(30, 12);
	cout << topCard1 << setw(8) << topCard2 << setw(8) << topCard3 << setw(8) << topCard4 << setw(8) << topCard5 << setw(8) << topCard6 << endl;
	gotoxy(30, 13);
	cout << bottomCard1 << setw(8) << bottomCard2 << setw(8) << bottomCard3 << setw(8) << bottomCard4 << setw(8) << bottomCard5 << setw(8) << bottomCard6 << endl;

	gotoxy(34, 15);

	for (int i = 0; i < 5; i++)
		cout << fRowGrid[i] << setw(8);

	gotoxy(31, 17);

	for (int i = 0; i < 4; i++)
		cout << sRowGrid[i] << setw(8);

	gotoxy(35, 19);

	for (int i = 0; i < 3; i++)
		cout << tRowGrid[i] << setw(8);

	gotoxy(39, 21);

	for (int i = 0; i < 2; i++)
		cout << foRowGrid[i] << setw(8);

	gotoxy(43, 23);

	cout << lRowGrid[0] << endl;

	cout << "Your cards: " << endl;
	cout << endl;
	
	// Giving cards to the player
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

	// Showing how many cards of each type you got
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

	// Input the place on the grid
	int cardPlace;
	cout << "Choose a number from 1 to " << cardSum << ":";
	cin >> cardPlace;

	// Checking if the number is a place on the grid
	while (cardPlace < 1 || cardPlace > cardSum)
	{
		cin.ignore();
		cout << "Invalid number. Please choose from 1 to " << cardSum << ":";
		cin >> cardPlace;
	}

	// Input the card
	string chosenCard;
	cout << "Choose a card(Please write the whole name. Example: 0[OR])";
	cin >> chosenCard;

	// Checking if you have this card
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