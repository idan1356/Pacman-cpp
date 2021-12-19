#ifndef _GHOST_H_
#define _GHOST_H_
#include "game_object.h"
#include "map.h"
#include "a_node.h"

#include <stack>
#include <queue>

class Ghost : public Game_Object {

public:
	Ghost(const Position& pos, const Color& color) : Game_Object('M', pos, Direction::RIGHT, color, pos) {}

	stack<Position> findPath(const Position& pacman, const Map& map) const;
};



#endif