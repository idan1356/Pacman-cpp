#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "game_initializer.h"
#include <filesystem>

class Menu {
private:
	bool color_mode = true;

	vector<string> getScreenFiles() const;

	void updateColorModeOption();
	void printInstructions();
	void returnToMenu();
	void startGame();
	void printMenu();
	void options();

public:
	void start();
};


#endif