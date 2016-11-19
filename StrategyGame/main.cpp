#include "game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

int main(int argc, char** argv)
{

	srand((unsigned)time(0));

	bool playAgain = true;
	while (playAgain)
	{
		game GP;
		GP.Play();

		cout << "\n\n\n                    Would you like to play again?";
		cout << "\n                    (Y)es or (N)o";

		while (true)
		{
			if (GetAsyncKeyState('Y'))
			{
				playAgain = true;
				break;
			}

			if (GetAsyncKeyState('N'))
			{
				playAgain = false;
				break;
			}
		}
	}
	
	return 0;
}