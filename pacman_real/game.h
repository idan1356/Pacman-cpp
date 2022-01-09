#ifndef _GAME_H_
#define _GAME_H_

#include "io_utils.h"
#include "pacman.h"
#include "ghost.h"
#include "map.h"
#include "fruit.h"

struct Game_State {
	short int lives = 3;
	short int score = 0;
};

class Game {
protected:
	Map				map;
	Pacman	        pacman = { {1,1}, Color::YELLOW };
	vector<Ghost>	ghost;
	Fruit			fruit;
	Position		legend;
	Difficulty		difficulty;
	int				lives = DEFAULT_NUM_OF_LIVES;
	int				score = 0;
	bool			saveFlag;


	bool isObjEatenByGhosts(const Game_Object& obj);
	void printMessage(const char* message);
	void addPointToScore() { score++; };
	void decreaseLives() { lives--; };
	void handleIsEaten(bool& game_over, Logger& log, int count);

	//Direction getDirectionFromStack(const Position& ghost, const Position& stack);

	void updateBreadcrumbs();
	void handlePlayerInput(Logger& log);
	void pacmanEatenEvent(Logger& log);
	void printParameters() const;

	void moveGhosts(int& counter, Logger& log);
	virtual void countdown();
	void pause();

	static Game instance;
public:
	Game(const Pacman& pacman, const vector<Ghost>& ghosts, const Map& map, const Position& legend, const Game_State& state, const Difficulty& difficulty, bool flag) :
		pacman(pacman), ghost(ghosts), map(map), fruit(map), legend(legend), lives(state.lives), score(state.score), difficulty(difficulty), saveFlag(flag) {};

	Game_State start();
};

#endif
