#include "mob.h"



mob::mob(unsigned int _range, unsigned int _health, char _name, unsigned int _min, unsigned int _max, bool _isPlayer1)
{
	range = _range;
	health = _health;
	name = _name;
	minAtt = _min;
	maxAtt = _max;
	srand((unsigned)time(0));
	isPlayer1 = 0;
	if (_isPlayer1)
		isPlayer1 |= (1);
}


mob::~mob()
{
}

unsigned int mob::getRange() { return range; }
unsigned int mob::getHealth() { return health; }
unsigned int mob::getRNGAtt() { return ((rand() % (maxAtt - minAtt)) + minAtt); }
char mob::getSymbol() { return name; }
bool mob::getP1() {}