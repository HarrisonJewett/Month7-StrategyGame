#pragma once
#include <random>
#include <ctime>

class mob
{
	unsigned int range;
	unsigned int health;
	unsigned int minAtt;
	unsigned int maxAtt;
	char name;
	char isPlayer1;

public:
	mob(unsigned int _range, unsigned int _health, char _name, unsigned int _min, unsigned int _max, bool _isPlayer1);
	~mob();


	//accessors
	unsigned int getRange();
	unsigned int getHealth();
	unsigned int getRNGAtt();
	char getSymbol();
	bool getP1();
};