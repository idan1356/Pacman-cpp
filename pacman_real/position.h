#ifndef _POSITION_H_
#define _POSITION_H_

#include "io_utils.h"

int const MAP_LENGTH = 79;
int const MAP_WIDTH = 24;

class Position {
private:
	int pos_x;
	int pos_y;

public:
	Position() : pos_x(0), pos_y(0) {}
	Position(int x, int y) : pos_x(x), pos_y(y) {}
	Position(const Position& pos) : pos_x(pos.pos_x), pos_y(pos.pos_y) {};

	int getX() const { return pos_x; };
	int getY() const { return pos_y; };

	void draw(char ch, Color color);
	void advance(Direction direction);

	bool isEqual(const Position& pos1);
};

#endif