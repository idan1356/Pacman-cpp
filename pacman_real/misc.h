#ifndef _MISC_H_
#define _MISC_H_

enum class Difficulty {
	BEST,
	GOOD,
	NOVICE
};

enum class Color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

enum class Direction { 
	UP,
	LEFT,
	DOWN,
	RIGHT,
	NONE,
	INVALID_KEY //invalid key pressed
};



const char GHOST_CHAR = '$';
const char PACMAN_CHAR = '@';

const char CORRIDOR = ' ';
const char BREADCRUMB = '.';
const char NO_BREADCRUMB_CORRIDOR = '%';
const char WALL = '#';

const int DEFAULT_NUM_OF_GHOSTS = 2;
const int DEFAULT_NUM_OF_LIVES = 3;

const int DEFAULT_MAP_WIDTH = 25;
const int DEFAULT_MAP_LENGTH = 80;

const int GAME_SPEED = 200;
const int ESC = 27;

const Color DEFAULT_MAP_COLOR = Color::BLUE;
const Color DEFAULT_BREADCRUMB_COLOR = Color::YELLOW;
const Color DEFAULT_PACMAN_COLOR = Color::YELLOW;
const Color DEFAULT_MESSAGE_COLOR = Color::WHITE;

const Color WIN_SCREEN_COLOR = Color::YELLOW;

//const Color colorOrder[4] = { Color::RED, Color::GREEN, Color::BROWN, Color::LIGHTMAGENTA };
#endif