#ifndef _GAME_INIT_H_
#define _GAME_INIT_H_
#include "game.h"

class Game_Initializer {
private:
	Map				map;
	vector<Pacman>	pacman;
	vector<Ghost>	ghost;

	const Color colorOrder[4] = { RED, GREEN, BROWN, LIGHTMAGENTA }; //make static

public:
	Game_Initializer(string file_name) : map(file_name) {
		if (map.getIsValidMap()) 
			initMap();
	};

	void startGame() { 
		if (map.getIsValidMap()) {
			Game game(pacman[0], ghost, map);
			game.start();
		}
		else {
			clear_screen();
			cout << "map is invalid" << endl;
			pressAnyKeyToContinue();
		}

	};
	void initMap();
	void initCell(Position pos);
	void printLegend(Position pos, Map& map);
};

#endif