#include "game.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>

using namespace std;

game::game()
{
	turnOrder[0] = War1 = new mob(1, 'W', 7, 14, true, 0, 1);
	turnOrder[1] = Sor1 = new mob(2, 'S', 1, 10, true, 1, 0);
	turnOrder[2] = Arc1 = new mob(4, 'A', 2, 7, true, 0, 0);

	turnOrder[3] = war2 = new mob(1, 'w', 7, 14, false, 5, 4);
	turnOrder[4] = sor2 = new mob(2, 's', 1, 10, false, 4, 5);
	turnOrder[5] = arc2 = new mob(4, 'a', 2, 7, false, 5, 5);
	gameCharBool = 1;

	board = new char*[6];
	for (int i = 0; i < 6; ++i)
	{
		board[i] = new char[6];

		for (int j = 0; j < 6; ++j)
			board[i][j] = '*';

	}
	for (int i = 0; i < 6; ++i)
		board[turnOrder[i]->getX()][turnOrder[i]->getY()] = turnOrder[i]->getSymbol();
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
	for (unsigned int i = 0; i < 6; ++i)
	{
		for (unsigned int  j = 0; j < 6; ++j)
		{
			cout << board[i][j];
		}
		cout << '\n';
	}
}