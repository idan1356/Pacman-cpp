#ifndef _GENERAL_H_
#define _GENERAL_H_

#include "game_menu.h"
#include "game_replayer.h" 

void replayGame(int argc, char* argv[]);
void menu(bool saveFlag);
bool isSave(int argc, char* argv[], bool& saveFlag);
bool isLoad(int argc, char* argv[]);

#endif