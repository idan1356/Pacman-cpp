#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include "misc.h"

#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

void gotoxy(int x, int y);
void setTextColor(Color color);
void hideCursor();
void clear_screen();

Direction keyToDirection(char key);
void pressAnyKeyToContinue();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string>

#endif

#endif