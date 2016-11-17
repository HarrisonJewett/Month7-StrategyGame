#include "game.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <random>

using namespace std;

game::game()
{
	turnOrder[0] = characters[0] = War1 = new mob(1, 'W', 7, 14, true, 0, 1);
	turnOrder[1] = characters[1] = Sor1 = new mob(2, 'S', 1, 10, true, 1, 0);
	turnOrder[2] = characters[2] = Arc1 = new mob(4, 'A', 2, 7, true, 0, 0);

	turnOrder[3] = characters[3] = war2 = new mob(1, 'w', 7, 14, false, 5, 4);
	turnOrder[4] = characters[4] = sor2 = new mob(2, 's', 1, 10, false, 4, 5);
	turnOrder[5] = characters[5] = arc2 = new mob(4, 'a', 2, 7, false, 5, 5);

	gameCharBool = 1;

	board = new char*[6];
	for (int i = 0; i < 6; ++i)
	{
		board[i] = new char[6];
		for (int j = 0; j < 6; ++j)
			board[i][j] = '*';
	}
	for (int i = 0; i < 6; ++i)
		board[characters[i]->getX()][characters[i]->getY()] = characters[i]->getSymbol();

	currentTurn = 1;
}

game::~game()
{
	delete War1;
	delete Sor1;
	delete Arc1;
	delete war2;
	delete sor2;
	delete arc2;
}

void game::Play()
{
	while (gameCharBool & (1))
	{
		//Set directions back to 0
		for (int i = 1; i < 5; ++i)
			gameCharBool &= ~(1 << i);

		for (unsigned int i = 0; i < 5; ++i)
		{
			short RNG = rand() % 6;
			temp = turnOrder[RNG];
			turnOrder[RNG] = turnOrder[i];
			turnOrder[i] = temp;
		}

		Update();
		Render();
	}
}

void game::Update()
{

}

void game::Render()
{
	system("cls");

	//Drawing the board
	for (unsigned int i = 0; i < 6; ++i)
	{
		for (unsigned int j = 0; j < 6; ++j)
		{
			cout << board[i][j];
		}
		cout << '\n';
	}

	//Displaying turn order
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 30, 0 };
	SetConsoleCursorPosition(output, position);
	cout << "Turn Order";

	for (unsigned int i = 0; i < 6; ++i)
	{
		position = { (short)30, (short)(currentTurn + i) };
		SetConsoleCursorPosition(output, position);
		cout << turnOrder[i]->getSymbol();
	}


	//Displaying health
	cout << "\n\n\nVigor\n";
	for (unsigned int i = 0; i < 3; ++i)
		cout << "P1: " << characters[i]->getSymbol() << ": " << characters[i]->getHealth() << "/20     ";
	cout << '\n';
	for (unsigned int i = 3; i < 6; ++i)
		cout << "P2: " << characters[i]->getSymbol() << ": " << characters[i]->getHealth() << "/20     ";


	while (true)
	{

	}

	if (currentTurn == 6)
		currentTurn = 1;
	else
		++currentTurn;
}

void game::checkMovementSpaces(unsigned short _x, unsigned short _y)
{
	if (_x == 5 && _y == 5)
	{
		if (board[4][5] == '*')
			gameCharBool |= (1 << 4);
		if (board[5][4] == '*')
			gameCharBool |= (1 << 1);

	}
	else if (_x == 5 && _y == 0)
	{
		if (board[4][0] == '*')
			gameCharBool |= (1 << 4);
		if (board[5][1] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x == 5)
	{
		if (board[5][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (board[4][_y] == '*')
			gameCharBool |= (1 << 4);
		if (board[5][_y + 1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x == 0 && _y == 5)
	{
		if (board[0][4] == '*')
			gameCharBool |= (1 << 1);
		if (board[1][5] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x == 0 && _y == 0)
	{
		if (board[1][0] == '*')
			gameCharBool |= (1 << 2);
		if (board[0][1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x == 0)
	{
		if (board[0][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (board[1][_y] == '*')
			gameCharBool |= (1 << 2);
		if (board[0][_y + 1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x > 0 && _x < 5 && _y == 0)
	{
		if (board[_x - 1][0] == '*')
			gameCharBool |= (1 << 4);
		if (board[_x][1] == '*')
			gameCharBool |= (1 << 3);
		if (board[_x + 1][0] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x > 0 && _x < 5 && _y == 5)
	{
		if (board[_x - 1][5] == '*')
			gameCharBool |= (1 << 4);
		if (board[_x][4] == '*')
			gameCharBool |= (1 << 1);
		if (board[_x + 1][5] == '*')
			gameCharBool |= (1 << 2);
	}
	else
	{
		if (board[_x][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (board[_x + 1][_y] == '*')
			gameCharBool |= (1 << 2);
		if (board[_x][_y + 1] == '*')
			gameCharBool |= (1 << 3);
		if (board[_x - 1][_y] == '*')
			gameCharBool |= (1 << 4);
	}
}