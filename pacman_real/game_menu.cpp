#include "game_menu.h"

void Menu::printInstructions() {
	cout << "Goal:" << endl;
	cout << "Guide Pacman around the maze and and eat all the little white dots while avoiding the ghosts." << endl << endl;

	cout << "Arrow keys for Pacman:" << endl;
	cout << "A or a : Left " << endl;
	cout << "D or d : Right" << endl;
	cout << "W or w : Up   " << endl;
	cout << "X or x : Down " << endl;
	cout << "S or s : Stay " << endl << endl;
	pressAnyKeyToContinue();
}

/*creates an instance of game, either with color or without, depends on color_mode option*/
void Menu::startGame() {
	vector<string> files = getScreenFiles();
	int numOfFiles = files.size();

	for (int i = 0; i < numOfFiles; i++) {
		Game_Initializer game(files[i]);
		game.startGame();
	}
}

void Menu::printMenu() {
	cout << "                                                             " << endl;
	cout << "                                                             " << endl;
	cout << "               ************ PACMAN MENU *************        " << endl;
	cout << "                     1. Start a new game                     " << endl;
	cout << "                     2. Options                              " << endl;
	cout << "                     3. Present instructions and keys        " << endl;
	cout << "                     4. Exit                                 " << endl;
	cout << "               **************************************        " << endl;
}

/*options menu */
void Menu::options() {
	cout << "Select Options:" << endl;
	cout << "1. Color mode:		      " << endl;
	cout << "2. Return to menu	        " << endl;
	updateColorModeOption();

	while (true) {
		char tempch;

		if (_kbhit()) {
			tempch = _getch();

			switch (tempch) {
			case '1':               /*toggle color_mode option*/
				color_mode = (color_mode + 1) % 2;  
				updateColorModeOption();
				break;
			case '2':
				return;
			default:
				continue;
			}
		}
	}
}

/*displays current status of the color_mode option*/
void Menu::updateColorModeOption() {
	gotoxy(26, 1);
	if (color_mode == true)
		cout << "on ";
	else
		cout << "off";
}

/*menu loop*/
void Menu::start() {
	char tempch;
	hideCursor();
	printMenu();

	while (true) {

		if (_kbhit()) {
			tempch = _getch();

			switch (tempch) {
			case '1':      
				startGame();
				returnToMenu();
				break;
			case '2':
				clear_screen();
				options();
				returnToMenu();
				break;
			case '3':
				clear_screen();
				printInstructions();
				returnToMenu();
				break;
			case '4':
				return;
			default:
				continue;
			}
		}
	}
}

/*returns back to main menu*/
void Menu::returnToMenu() {
	clear_screen();
	printMenu();
}

vector<string> Menu::getScreenFiles() const {
	vector<string> files;
	string extension = ".screen";
	fs::path path = fs::current_path();

	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == extension)
			files.push_back(p.path().stem().string() + extension);
	}

	return files;
}