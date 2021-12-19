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
	Game_Initializer(string file_name, Game_State state, Difficulty difficulty, bool color) : map(file_name, color), state(state), difficulty(difficulty), colorMode(color) {
		if (map.getIsValidMap()) 
			initMap();
	};

	Game_Initializer(string file_name, bool color) : map(file_name, color) {
		if (map.getIsValidMap())
			initMap();
	};

	Game_State startGame() { 
		if (map.getIsValidMap()) {
			Game game(pacman[0], ghost, map, legend, state, difficulty);
			return game.start();
		}
		else {
			clear_screen();
			cout << "map is invalid" << endl;
			pressAnyKeyToContinue();
		}

	};
	void initMap();
	void initCell(Position pos);
};



#endif