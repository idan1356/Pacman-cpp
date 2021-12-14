#ifndef _GHOST_H_
#define _GHOST_H_
#include "game_object.h"
#include "map.h"

class Ghost : public Game_Object {

public:
	Ghost(Position pos, Color color) : Game_Object('M', pos, RIGHT, color, pos) {}
};

#endif