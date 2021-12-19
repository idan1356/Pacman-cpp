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

#endif