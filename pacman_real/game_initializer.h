#ifndef _GAME_INIT_H_
#define _GAME_INIT_H_
#include "game.h"
#include "game_replayer.h"

class Game_Initializer {
protected:
	Map				map;
	vector<Pacman>	pacman;
	vector<Ghost>	ghost;
	Position		legend;
	Game_State		state;
	Difficulty		difficulty;
	bool			colorMode;
	bool			saveMode;
	const Color		colorOrder[4] = { Color::RED, Color::GREEN, Color::BROWN, Color::LIGHTMAGENTA }; //make static

public:
	Game_Initializer(const string& file_name,const Game_State& state,const Difficulty& difficulty, bool color, bool saveFlag) 
		: map(file_name, color), state(state), difficulty(difficulty), colorMode(color), saveMode(saveFlag) {
		if (map.getIsValidMap()) 
			initMap();
	};

//	Game_Initializer(const string& file_name, const bool color) : map(file_name, color) {
//		if (map.getIsValidMap())
//			initMap();
//	};

	Game_State startGame() const;
	Game_State replay(bool silentFlag);
	void initMap();
	void initCell(Position pos);
};



#endif