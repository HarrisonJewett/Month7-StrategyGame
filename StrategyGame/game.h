#pragma once
#include "mob.h"
class game
{
	mob *War1 = nullptr;
	mob* Sor1 = nullptr;
	mob* Arc1 = nullptr;

	mob* war2 = nullptr;
	mob* sor2 = nullptr;
	mob* arc2 = nullptr;

	mob* turnOrder[6];

	char** board;

	//bit 1 is continue playing
	char gameCharBool;
public:
	game();
	~game();

	//Functions
	void Play();
	void Update();
	void Render();
};