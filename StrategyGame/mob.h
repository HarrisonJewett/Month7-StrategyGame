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
	unsigned short xCoor;
	unsigned short yCoor;
		
	char charBool;
	//bit 1 reps Player 1
	//bit 2 reps isAlive

public:
	mob(unsigned int _range, char _name, unsigned int _min, unsigned int _max, bool _isPlayer1, unsigned short _x, unsigned short _y);
	~mob();


	//accessors
	unsigned int getRange();
	unsigned int getHealth();
	unsigned int getRNGAtt();
	char getSymbol();
	bool getP1();
	void killMob();
	void takeDamage(unsigned int _damageDelt);
	unsigned short getX() { return xCoor; }
	unsigned short getY() { return yCoor; }
	void setX(unsigned short _x) { xCoor = _x; }
	void setY(unsigned short _y) { yCoor = _y; }
	bool isAlive() { return (charBool & (1 << 1)) != 0; }
	void setSymbol(char _newSymbol) { name = _newSymbol; }
};