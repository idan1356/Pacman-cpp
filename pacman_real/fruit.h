#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "game_object.h"

class Fruit : public Game_Object {
private:
	bool isActivated = false;

public:
	Fruit(const Map& map) : Game_Object(getRandNum(), map.getRandPositionOnMap(), Direction::RIGHT, Color::WHITE, map.getRandPositionOnMap()) {};
	virtual void moveNovice(Map& map, Logger& log, int i = -1);

	const bool& getIsActivated() const { return isActivated; };
	void toggle(Map& map, Logger& log);
	string logToggle();
	char getRandNum() const;
};
#endif