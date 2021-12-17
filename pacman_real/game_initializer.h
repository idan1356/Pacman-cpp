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
	const Color		colorOrder[4] = { RED, GREEN, BROWN, LIGHTMAGENTA }; //make static

public:
	Game_Initializer(string file_name, Game_State state) : map(file_name), state(state)  {
		if (map.getIsValidMap()) 
			initMap();
	};

	Game_Initializer(string file_name) : map(file_name) {
		if (map.getIsValidMap())
			initMap();
	};

	Game_State startGame() { 
		if (map.getIsValidMap()) {
			Game game(pacman[0], ghost, map, legend, state);
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