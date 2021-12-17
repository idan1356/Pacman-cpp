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
	int numOfFiles = files.size();
	Game_State state;

	if (files.size() == 0) {
		clear_screen();
		cout << "No screen files found" << endl;
		pressAnyKeyToContinue();
		return;
	}

	if (screen_selected == numOfFiles) {
		for (int i = 0; i < numOfFiles; i++) {
			Game_Initializer game(files[i], state , difficulty, color_mode);
			state = game.startGame();
			
			if (state.lives == 0)
				break;
		}
	}
	else {
		Game_Initializer game(files[screen_selected], state, difficulty, color_mode);
		state = game.startGame();
	}

	if (state.lives == 0)
		gameLostScreen();
	else
		gameWonScreen();
	pressAnyKeyToContinue();
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
	cout << "2. Difficulty	        " << endl;
	cout << "3. Screen Selected      " << endl;
	cout << "4. Return to menu	        " << endl;

	updateColorModeOption();
	updateDifficulty();
	updateScreenSelected();

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
				difficulty = Difficulty((int(difficulty) + 1) % 3);
				updateDifficulty();
				break;
			case '3':
				screen_selected = (screen_selected + 1) % (files.size() + 1);
				updateScreenSelected();
				break;
			case '4':
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

void Menu::updateDifficulty() {
	gotoxy(26, 2);
	if(difficulty == Difficulty::BEST)
		cout << "BEST  ";
	else if (difficulty == Difficulty::GOOD)
		cout << "GOOD  ";
	else if (difficulty == Difficulty::NOVICE)
		cout << "NOVICE  ";
}

void Menu::updateScreenSelected() {
	gotoxy(26, 3);
	if (screen_selected == files.size())
		cout << "full game    ";
	else
		cout << files[screen_selected] << "    ";
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

	std::sort(files.begin(), files.end());

	return files;
}

void Menu::gameLostScreen() {
	const char ghostArt[4][50] = {
		"     .-.   .-.     .--.                         ",
		"    | OO| | OO|   / _.-' .-.   .-.  .-.   .''.  ",
		"    |   | |   |   \  '-. '-'   '-'  '-'   '..'  ",
		"    '^^^' '^^^'    '--'                         ",
	};

	clear_screen();

	for (int i = 0; i < 4; i++)
		cout << ghostArt[i] << endl;

	cout << "      oh no! you lost" << endl;
}

void Menu::gameWonScreen() {
	const char tropyArt[10][27] = {
		"             ___________  ",
		"            '._==_==_=_.' ",
		"            .-\:      /-. ",
		"           | (|:. #1  |) |",
		"            '-|:.     |-' ",
		"              \::.    /   ",
		"               '::. .'    ",
		"                 ) (      ",
		"               _.' '._    ",
		"              `--------`  ",
	};

	clear_screen();
	setTextColor(WIN_SCREEN_COLOR);

	for (int i = 0; i < 10; i++)
		cout << tropyArt[i] << endl;

	setTextColor(WHITE);
	cout << "      Congratulations! you won" << endl;

}
