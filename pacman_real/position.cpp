#include "position.h"

/*draws a char at a given position*/
void Position::draw(char ch, Color color) {
	setTextColor(color);
	gotoxy(pos_x, pos_y);
	cout << ch << endl;
	setTextColor(WHITE);
}

void Position::advance(Direction dir) {
	switch (dir) {
	case UP:
		--pos_y;
		break;
	case DOWN: 
		++pos_y;
		break;
	case LEFT: 
		--pos_x;
		break;
	case RIGHT:
		++pos_x;
		break;
/*	case NONE: no change to pos_x, pos_y */
	}
}

/*returns true if two positions are equal, returns false otherwise*/
bool Position::isEqual(const Position& pos1) {
	return ((pos1.pos_x == pos_x) && (pos1.pos_y == pos_y));
}




