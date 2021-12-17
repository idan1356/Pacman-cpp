#ifndef _MISC_H_
#define _MISC_H_

enum class Difficulty {
	BEST,
	GOOD,
	NOVICE
};

enum Color {
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

enum Direction { 
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

const int GAME_SPEED = 300;
const int ESC = 27;

const Color DEFAULT_MAP_COLOR = BLUE;
const Color DEFAULT_BREADCRUMB_COLOR = YELLOW;
const Color DEFAULT_PACMAN_COLOR = YELLOW;
const Color DEFAULT_MESSAGE_COLOR = WHITE;

const Color WIN_SCREEN_COLOR = YELLOW;

const Color colorOrder[4] = { RED, GREEN, BROWN, LIGHTMAGENTA };
#endif