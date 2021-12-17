#ifndef _GHOST_H_
#define _GHOST_H_
#include "game_object.h"
#include "map.h"
#include "a_node.h"

#include <stack>
#include <queue>

class Ghost : public Game_Object {

public:
	Ghost(Position pos, Color color) : Game_Object('M', pos, RIGHT, color, pos) {}

	stack<Position> findPath(Position pacman, Map& map);

	void moveBest(Map& map, Position pacman, int counter);
};



#endif