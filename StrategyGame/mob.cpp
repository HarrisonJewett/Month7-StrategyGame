#include "mob.h"



mob::mob(unsigned int _range, char _name, unsigned int _min, unsigned int _max, bool _isPlayer1, unsigned short _x, unsigned short _y)
{
	range = _range;
	health = 20;
	name = _name;
	minAtt = _min;
	maxAtt = _max;
	srand((unsigned)time(0));
	charBool = 0;
	if (_isPlayer1)
		charBool |= (1);	
	charBool |= (1 << 1);
	xCoor = _x;
	yCoor = _y;
}

mob::~mob(){}

unsigned int mob::getRange() { return range; }
unsigned int mob::getHealth() { return health; }
unsigned int mob::getRNGAtt() { return ((rand() % (maxAtt - minAtt)) + minAtt); }
char mob::getSymbol() { return name; }
bool mob::getP1() { return (charBool & 1); }

void mob::killMob(mob _mobToKill) { _mobToKill.charBool &= ~(1 << 1); }
//Take Damage might cause a crash if damage delt is higher than remaining health

void mob::takeDamage(unsigned int _damageDelt) { health -= _damageDelt; };