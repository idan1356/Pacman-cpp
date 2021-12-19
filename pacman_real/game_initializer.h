#ifndef _GAME_INIT_H_
#define _GAME_INIT_H_
#include "game.h"

class Game_Initializer {
private:
	Map				map;
	vector<Pacman>	pacman;
	vector<Ghost>	ghost;
	Position		legend;
	Game_State		state;
	Difficulty		difficulty;
	bool			colorMode;
	const Color		colorOrder[4] = { Color::RED, Color::GREEN, Color::BROWN, Color::LIGHTMAGENTA }; //make static

public:
	Game_Initializer(const string& file_name,const Game_State& state,const Difficulty& difficulty, bool color) : map(file_name, color), state(state), difficulty(difficulty), colorMode(color) {
		if (map.getIsValidMap()) 
			initMap();
	};

	Game_Initializer(const string& file_name, const bool color) : map(file_name, color) {
		if (map.getIsValidMap())
			initMap();
	};

	Game_State startGame() const;
	void initMap();
	void initCell(Position pos);
};



#endif