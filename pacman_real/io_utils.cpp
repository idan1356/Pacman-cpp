#include "io_utils.h"

using namespace std;


/*converts key to direction*/
Direction keyToDirection(char key) {
	switch (key) {
	case 'W':
	case 'w':
		return Direction::UP;
	case 'X':
	case 'x':
		return Direction::DOWN;
	case 'A':
	case 'a':
		return Direction::LEFT;
	case 'D':
	case 'd':
		return Direction::RIGHT;
	case 'S':
	case 's':
		return Direction::NONE;
	default:
		return Direction::INVALID_KEY;
	}
}

void pressAnyKeyToContinue() {
	cout << "Press any key to return to menu...";
	while (!_kbhit()) {
		continue;
	}
}

#ifndef WINDOWS
void gotoxy(int x, int y) {}
int _getch(void) { return 0; }
int _kbhit(void) { return 0; }
void Sleep(unsigned long) {}
void setTextColor(Color color) {}
void hideCursor() {}
void clear_screen() {}
#else

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void hideCursor(){
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);   //second argument need pointer
}

void clear_screen(){
	system("cls");
}

string dirToStr(const Direction& dir) {
	switch (dir) {
	case Direction::UP:
		return "up";
		break;
	case Direction::DOWN:
		return "down";
		break;
	case Direction::RIGHT:
		return "right";
		break;
	case Direction::LEFT:
		return "left";
		break;
	case Direction::NONE:
		return "inplace";
		break;
	default:
		throw invalid_argument("Invalid direction given");
	}
}

vector<string> getFiles(string extension) {
	vector<string> files;
	fs::path path = fs::current_path();

	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == extension)
			files.push_back(p.path().stem().string() + extension);
	}

	std::sort(files.begin(), files.end());

	return files;
}

string remove_extension(const string& filename) {
	int lastdot = filename.find_last_of(".");
	if (lastdot == string::npos) return filename;
	return filename.substr(0, lastdot);
}



#endif