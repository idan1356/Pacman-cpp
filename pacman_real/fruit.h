#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "game_object.h"

class Fruit : public Game_Object {
private:
	bool isActivated = true;

public:
	Fruit(const Map& map) : Game_Object(getRandNum(), map.getRandPositionOnMap(), Direction::RIGHT, Color::WHITE, map.getRandPositionOnMap()) {};
	virtual void moveNovice(Map& map);
	void toggle(Map& map);
	char getRandNum() const;
};
#endif