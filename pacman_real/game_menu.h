#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "game_initializer.h"
#include <filesystem>




class Menu {
private:
	bool			color_mode = true;
	vector<string>	files = getScreenFiles();
	Difficulty		difficulty = Difficulty::GOOD;
	int				screen_selected;

	vector<string> getScreenFiles() const;
	void updateScreenSelected();
	void updateDifficulty();
	void updateColorModeOption();
	void printInstructions();
	void returnToMenu();
	void startGame();
	void printMenu();
	void options();

	void gameLostScreen();
	void gameWonScreen();
	void endgameScreen();

public:
	Menu() : files(getScreenFiles()), screen_selected(files.size()) {};
	void start();
};


#endif