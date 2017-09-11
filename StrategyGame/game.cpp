#include "game.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <random>
#include <conio.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESCAPE 27
#define WARRIOR 119
#define SORCERER 115
#define ARCHER 97


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

	board = new char**[6];
	for (int i = 0; i < 6; ++i)
	{
		board[i] = new char*[6];
		for (int j = 0; j < 6; ++j)
		{
			board[i][j] = new char();
			*board[i][j] = '*';
		}
	}
	for (int i = 0; i < 6; ++i)
		*board[characters[i]->getX()][characters[i]->getY()] = characters[i]->getSymbol();

	currentTurn = 0;


}

game::~game()
{
	delete War1;
	delete Sor1;
	delete Arc1;
	delete war2;
	delete sor2;
	delete arc2;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[]board;
}

void game::Play()
{
	while (gameCharBool & (1))
	{


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
	while (currentTurn != 6)
	{
		loop |= 1;

		drawBoard();

		//Set directions back to 0
		for (int i = 1; i < 8; ++i)
			gameCharBool &= ~(1 << i);
		if (turnOrder[currentTurn]->isAlive())
		{
			checkMovementSpaces(turnOrder[currentTurn]->getX(), turnOrder[currentTurn]->getY());

			//Movement Phase
			if ((gameCharBool & (1 << 1)) == 0 && (gameCharBool & (1 << 2)) == 0 && (gameCharBool & (1 << 3)) == 0 && (gameCharBool & (1 << 4)) == 0)
			{
				cout << "\nNo valid moves. Press enter to move to attack phase.";
				while (true)
				{
					if (GetAsyncKeyState(VK_RETURN))
						break;
				}
			}

			else
			{
				cout << "\nUse arrow keys to move. Press ESC to skip your movement.";

				while (loop)
				{
					if (_kbhit())
					{
						char input = _getch();
						if (input == UP_ARROW || input == DOWN_ARROW || input == LEFT_ARROW || input == RIGHT_ARROW || input == ESCAPE)
						{
							*board[turnOrder[currentTurn]->getX()][turnOrder[currentTurn]->getY()] = '*';

							switch (input)
							{
							case UP_ARROW:
								if (gameCharBool & (1 << 1))
									turnOrder[currentTurn]->setY(turnOrder[currentTurn]->getY() - 1);
								break;
							case RIGHT_ARROW:
								if (gameCharBool & (1 << 2))
									turnOrder[currentTurn]->setX(turnOrder[currentTurn]->getX() + 1);
								break;
							case DOWN_ARROW:
								if (gameCharBool & (1 << 3))
									turnOrder[currentTurn]->setY(turnOrder[currentTurn]->getY() + 1);
								break;
							case LEFT_ARROW:
								if (gameCharBool & (1 << 4))
									turnOrder[currentTurn]->setX(turnOrder[currentTurn]->getX() - 1);
								break;
							case ESCAPE:
								break;
							}
							loop = 0;
							*board[turnOrder[currentTurn]->getX()][turnOrder[currentTurn]->getY()] = turnOrder[currentTurn]->getSymbol();
						}
					}
				}
				drawBoard();
			}

			//Attack Phase
			//distance = abs (x2 – x1) + abs (y2 – y1)

			cout << '\n';

			if (turnOrder[currentTurn]->getP1())
			{
				for (unsigned int i = 3; i < 6; ++i)
				{
					if (characters[i]->isAlive())
					{
						if ((unsigned int)((abs(characters[i]->getX() - turnOrder[currentTurn]->getX())) + abs(characters[i]->getY() - turnOrder[currentTurn]->getY()) <= turnOrder[currentTurn]->getRange()))
							gameCharBool |= (1 << (2 + i));
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < 3; ++i)
				{
					if (characters[i]->isAlive())
					{
						if ((unsigned int)((abs(characters[i]->getX() - turnOrder[currentTurn]->getX())) + abs(characters[i]->getY() - turnOrder[currentTurn]->getY()) <= turnOrder[currentTurn]->getRange()))
							gameCharBool |= (1 << (5 + i));
					}
				}
			}
			if ((gameCharBool & (1 << 5)) != 0 || (gameCharBool & (1 << 6)) != 0 || (gameCharBool & (1 << 7)) != 0)
			{
				cout << "Possible Targets:";
				if (gameCharBool & (1 << 5))
					cout << "\n(W)arrior";
				if (gameCharBool & (1 << 6))
					cout << "\n(S)orcerer";
				if (gameCharBool & (1 << 7))
					cout << "\n(A)rcher";
				cout << "\nPress ESC to skip your attack";
				while (true)
				{
					if (_kbhit())
					{
						char _input = _getch();
						if (_input == WARRIOR)
						{
							if (gameCharBool & (1 << 5))
							{
								if (turnOrder[currentTurn]->getP1())
									characters[3]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								else
									characters[0]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								break;
							}
							else
								break;
						}
						if (_input == SORCERER)
						{
							if (gameCharBool & (1 << 6))
							{
								if (turnOrder[currentTurn]->getP1())
									characters[4]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								else
									characters[1]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								break;
							}
							else
								break;
						}
						if (_input == ARCHER)
						{
							if (gameCharBool & (1 << 7))
							{
								if (turnOrder[currentTurn]->getP1())
									characters[5]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								else
									characters[2]->takeDamage(turnOrder[currentTurn]->getRNGAtt());
								break;
							}
							else
								break;
						}
						if (_input == ESCAPE)
							break;
					}
				}

				for (int i = 0; i < 6; ++i)
				{
					if (characters[i]->getHealth() < 1)
					{
						characters[i]->setSymbol('D');
						characters[i]->killMob();
						*board[characters[i]->getX()][characters[i]->getY()] = 'D';
					}
				}
			}
		}
		++currentTurn;
		if (!characters[0]->isAlive() && !characters[1]->isAlive() && !characters[2]->isAlive())
			gameOver(false);
		else if (!characters[3]->isAlive() && !characters[4]->isAlive() && !characters[5]->isAlive())
			gameOver(true);

	}
	currentTurn = 0;
}

void game::drawBoard()
{
	system("cls");


	//Drawing the board
	for (unsigned int i = 0; i < 6; ++i)
	{
		for (unsigned int j = 0; j < 6; ++j)
			cout << *board[j][i];
		cout << '\n';
	}

	//Displaying turn order
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 30, 0 };
	SetConsoleCursorPosition(output, position);
	cout << "Turn Order";

	position = { 33, currentTurn + 1 };
	SetConsoleCursorPosition(output, position);
	cout << "<-";

	for (unsigned int i = 0; i < 6; ++i)
	{
		position = { (short)30, (short)(1 + i) };
		SetConsoleCursorPosition(output, position);
		cout << turnOrder[i]->getSymbol();
	}

	//Displaying health
	cout << "\n\n\nHealth\n";
	for (unsigned int i = 0; i < 3; ++i)
		cout << "P1: " << characters[i]->getSymbol() << ": " << characters[i]->getHealth() << "/20     ";
	cout << '\n';
	for (unsigned int i = 3; i < 6; ++i)
		cout << "P2: " << characters[i]->getSymbol() << ": " << characters[i]->getHealth() << "/20     ";


}

void game::checkMovementSpaces(unsigned short _x, unsigned short _y)
{
	if (_x == 5 && _y == 5)
	{
		if (*board[4][5] == '*')
			gameCharBool |= (1 << 4);
		if (*board[5][4] == '*')
			gameCharBool |= (1 << 1);

	}
	else if (_x == 5 && _y == 0)
	{
		if (*board[4][0] == '*')
			gameCharBool |= (1 << 4);
		if (*board[5][1] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x == 5 && _y < 5 && _y > 0)
	{
		if (*board[5][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (*board[4][_y] == '*')
			gameCharBool |= (1 << 4);
		if (*board[5][_y + 1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x == 0 && _y == 5)
	{
		if (*board[0][4] == '*')
			gameCharBool |= (1 << 1);
		if (*board[1][5] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x == 0 && _y == 0)
	{
		if (*board[1][0] == '*')
			gameCharBool |= (1 << 2);
		if (*board[0][1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x == 0 && _y < 5 && _y > 0)
	{
		if (*board[0][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (*board[1][_y] == '*')
			gameCharBool |= (1 << 2);
		if (*board[0][_y + 1] == '*')
			gameCharBool |= (1 << 3);
	}
	else if (_x > 0 && _x < 5 && _y == 0)
	{
		if (*board[_x - 1][0] == '*')
			gameCharBool |= (1 << 4);
		if (*board[_x][1] == '*')
			gameCharBool |= (1 << 3);
		if (*board[_x + 1][0] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x > 0 && _x < 5 && _y == 5)
	{
		if (*board[_x - 1][5] == '*')
			gameCharBool |= (1 << 4);
		if (*board[_x][4] == '*')
			gameCharBool |= (1 << 1);
		if (*board[_x + 1][5] == '*')
			gameCharBool |= (1 << 2);
	}
	else if (_x > 0 && _x < 5 && _y < 5 && _y > 0)
	{
		if (*board[_x][_y - 1] == '*')
			gameCharBool |= (1 << 1);
		if (*board[_x + 1][_y] == '*')
			gameCharBool |= (1 << 2);
		if (*board[_x][_y + 1] == '*')
			gameCharBool |= (1 << 3);
		if (*board[_x - 1][_y] == '*')
			gameCharBool |= (1 << 4);
	}
}

void game::gameOver(bool _isPlayer1)
{
	system("cls");
	if (_isPlayer1)
		cout << "\n\n\n                    PLAYER 1 WINS!!!";
	else
		cout << "\n\n\n                    PLAYER 2 WINS!!!";


	gameCharBool = 0;


}

//Push to public Repo