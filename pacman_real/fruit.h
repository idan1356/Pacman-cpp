#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "game_object.h"

class Fruit : public Game_Object {
private:
	bool isActivated = true;

public:
	Fruit(Map map) : Game_Object(getRandNum(), map.getRandPositionOnMap(), RIGHT, WHITE, map.getRandPositionOnMap()) {};
	virtual void moveNovice(Map map);
	void toggle(Map map);
	char getRandNum();
};
#endif