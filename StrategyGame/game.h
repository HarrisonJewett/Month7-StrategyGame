#pragma once
#include "mob.h"



class game
{
	mob* War1 = nullptr;
	mob* Sor1 = nullptr;
	mob* Arc1 = nullptr;

	mob* war2 = nullptr;
	mob* sor2 = nullptr;
	mob* arc2 = nullptr;

	mob* characters[6];
	mob* turnOrder[6];
	mob* temp = nullptr;

	char** board;

	//bit 1 is continue playing
	//2 is north
	//3 is east
	//4 is south
	//5 is west
	char gameCharBool;

	unsigned short currentTurn;
public:
	game();
	~game();

	//Functions
	void Play();
	void Update();
	void Render();
	void checkMovementSpaces(unsigned short _x, unsigned short _y);
};