#include "general.h"

void menu(bool saveFlag) {
	vector<string> files = getFiles(".screen");
	Menu menu(files);
	menu.start(saveFlag);
}

void replayGame(int argc, char* argv[]) {
	Game_State state;
	vector<string> res_files = getFiles(".result");

	for (auto& file : res_files) {
		string screen_file = remove_extension(file) + ".screen";

		if (experimental::filesystem::exists(screen_file)) {
			Game_Initializer game(screen_file, state, Difficulty::BEST, true, false);
			bool silentFlag = (argc == 3 && strcmp(argv[2], "[-silent]") == 0);
			state = game.replay(silentFlag);

			if (state.lives == 0)
				break;
		}
		else
			throw invalid_argument("map file does not exist for this record");
	}
}

bool isLoad(int argc, char* argv[]) {
	return (argc == 2 && (strcmp("-load", argv[1]) == 0)) ||
		(argc == 3 && (strcmp("-load", argv[1]) == 0) && (strcmp("[-silent]", argv[2]) == 0));
}

bool isSave(int argc, char* argv[], bool& saveFlag) {
	if (argc == 1)
		return true;

	else if ((argc == 2 && strcmp("-save", argv[1]) == 0) ||
		(argc == 3 && strcmp("-save", argv[1]) == 0) && strcmp("[-silent]", argv[2]) == 0) {
		saveFlag = true;
		return true;
	}
	else
		return false;

}

