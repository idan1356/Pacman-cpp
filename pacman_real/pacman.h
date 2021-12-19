#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "game_object.h"

class Pacman: public Game_Object {

private:

public:
	Pacman(Position pos) : Game_Object(PACMAN_CHAR, pos, Direction::NONE, DEFAULT_PACMAN_COLOR, pos) {}
	Pacman(Position pos, Color color) : Game_Object(PACMAN_CHAR, pos, Direction::NONE, color, pos) {}
	Pacman() {};

	void adjustToInput(Map map, char ch);
	void useSecretTunnel(Map map);
	void movePacman(Map map);
};

#endif