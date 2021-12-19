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
	void updateScreenSelected() const;
	void updateDifficulty() const;
	void updateColorModeOption() const;
	void printInstructions() const;
	void returnToMenu() const;
	void startGame() const;
	void printMenu() const;
	void options();

	void gameLostScreen() const;
	void gameWonScreen() const;
	void endgameScreen() const;

public:
	Menu() : files(getScreenFiles()), screen_selected(files.size()) {};
	void start();
};


#endif