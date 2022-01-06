#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "game_object.h"
#include "logger.h"

class Pacman: public Game_Object {

private:

public:
	Pacman(const Position& pos) : Game_Object(PACMAN_CHAR, pos, Direction::NONE, DEFAULT_PACMAN_COLOR, pos) {}
	Pacman(const Position& pos, const Color& color) : Game_Object(PACMAN_CHAR, pos, Direction::NONE, color, pos) {}
	Pacman() {};

	void adjustToInput(Map& map, Logger& log, char ch);
	void useSecretTunnel(Map& map);
	void movePacman(Map& map, Logger& log);
};

#endif