#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "game_initializer.h"
#include <filesystem>

class Menu {
private:
	bool			color_mode = true;
	vector<string>	files;
	Difficulty		difficulty = Difficulty::GOOD;
	int				screen_selected;

	void updateScreenSelected() const;
	void updateDifficulty() const;
	void updateColorModeOption() const;
	void printInstructions() const;
	void returnToMenu() const;
	void startGame(bool saveFlag) const;
	void printMenu() const;
	void options();

	void gameLostScreen() const;
	void gameWonScreen() const;
	void endgameScreen() const;

public:
	Menu(vector<string> files) : files(files), screen_selected(files.size()) {};
	void start(bool saveFlag);
};


#endif