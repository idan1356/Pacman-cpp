#ifndef _REPLAYER_H_
#define _REPLAYER_H_

#include "game_initializer.h"

class Game_Replayer : public Game {
private:
	ifstream  steps;
	ifstream  res;

public:
	Game_Replayer(string file, const Pacman& pacman, const vector<Ghost>& ghosts, const Map& map,
		           const Position& legend, const Game_State& state, const Difficulty& difficulty, bool saveFlag)
								  : steps(remove_extension(file) + ".steps"),
								  res(remove_extension(file) + ".result"),
								  Game(pacman, ghosts, map, legend, state, Difficulty::NOVICE, saveFlag) {};

	void readStep(int count);
	void parseLine(const string& line);
	void handleIsEatenRec(int& count, Logger& log, bool& gameOver);
	Game_State replay(bool silentFlag);

	bool isClearedLogged(int& count);
	bool isEatenLogged(int count);
	virtual void countdown() {};

	static Direction strToDir(string str);

};

#endif
