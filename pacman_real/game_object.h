#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <iostream>
#include "position.h"
#include "map.h"
#include "misc.h"

class Game_Object {
private:
	char		obj_char;
	Position	obj_pos;
	Direction	obj_dir;
	Color		obj_color;

	const Position	obj_init_pos;

public:
	Game_Object(char ch, Position pos, Direction dir, Color color, Position init_pos);
	Game_Object();

	Direction getDirection() const { return obj_dir; };
	Position  getPosition() const { return obj_pos; };
	Position getInitPosition() const { return obj_init_pos; };
	Color getColor() const { return obj_color; };
	Position  getNextPosition();

	char getchar() const { return obj_char; };

	void setPosition(const Position& pos);
	void setDirection(const Direction& direction); 
	void setDirection(char key);
	void setchar(char ch) { obj_char = ch; };

	void teleportObject(Position pos, Map map);
	void moveToInitPos(Map map);
	void moveObject(Map map);

	virtual void moveNovice(Map map);
};

#endif