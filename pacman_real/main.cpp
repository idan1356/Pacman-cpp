#include "general.h"

void replayGame(char* argv[]);
void menu();

int main(int argc, char* argv[]) {
	bool saveFlag = false;
	
	if (isSave(argc, argv, saveFlag)) {
		menu(saveFlag);
	}

	else if (isLoad(argc, argv)) {
		try {
			replayGame(argc, argv);
			clear_screen();
			cout << "replay valid" << endl;
		}
		catch (...) {
			clear_screen();
			cout << "replay invalid" << endl;
		}
	}
	else 
		throw invalid_argument("invalid argument given");
}



// logger always active, create enable/disable based on argument
// game over/game won for result -done
// result file is valid/invalid