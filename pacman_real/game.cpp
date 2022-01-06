#include "game.h"
#include "stack"
//game loop
Game_State Game::start() {
	int count;
	bool gameOver;
	stack<Position> stacks[4];
	Logger log;

	if (saveFlag) {
		log.activate();
		log.write(map.getMapName());
	}

	count = 0;
	gameOver = false;
	hideCursor();
//	countdown();

	while (gameOver == false) { 
		gotoxy(0, 0);
		cout << count << endl;

		log.newTurn(count);
		handleIsEaten(gameOver, log, count);
		Sleep(GAME_SPEED);
		handlePlayerInput(log);     /*handles pacman movement and pause status according to player input*/
		updateBreadcrumbs();       /*updates breadcrumb based on pacmans location*/
		handleIsEaten(gameOver, log, count);

		if (map.getBreadcrumbCount() == 0) {
			gameOver = true;
			break;
		}
		if (count % 2 == 0) 
			moveGhosts(count, stacks, log);

		if (count % 3 == 0) {
			if ((rand() % 55) == 1) 
				fruit.toggle(map, log);
			else
				fruit.moveNovice(map, log, -1);
		}

		printParameters();
		count++;
	}

	log.logToRes("-----------------");
	if (lives == 0) {
		log.logToRes("level lost");
	}
	else {
		log.logToRes(to_string(count));
		log.logToRes("level cleared");
	}

	clear_screen();
	log.close();
	Game_State state = { lives, score };
	return  state;
}


/*pauses the game*/
void Game::pause() {
	char tempch = 1;

	while(tempch != ESC) {      /*enters a loop that continues as long as the player didnt press ESC*/
		printMessage("Game Paused");

		if (_kbhit())
			tempch = _getch();
	} 
}

/*prints the score and lives at the buttom of the screen*/
void Game::printParameters() const {
	int x = legend.getX();
	int y = legend.getY();

	gotoxy(x + 1 , y + 1);
	cout << "score:" << score;
	gotoxy(x + 11, y + 1);
	cout << "lives:" << lives;
}

/*handles pacman eaten event, 
moves pacman and the ghosts back to their intitial position and starts a small countdown*/
void Game::pacmanEatenEvent() {
	printParameters();

	pacman.moveToInitPos(map);
	pacman.setDirection(Direction::NONE);

	for (int i = 0; i < ghost.size(); i++)
		ghost[i].moveToInitPos(map);

	countdown();
}

/*prints a custom message at the buttom-center of the screen and pauses for almost a second*/
void Game::printMessage(const char* string) {
	setTextColor(DEFAULT_MESSAGE_COLOR);
	gotoxy(40, 19);
	cout << string;
	Sleep(900);

	gotoxy(40, 19);
	cout << "                   ";  
	map.fixMap();

	setTextColor(Color::WHITE);
}

/*iterates through the array of ghosts and moves them 1 step*/
//each ghost has a change to sample pacmans current position and create a short path to its position
//the sample rate of pacmans position changes according to the difficulty
void Game::moveGhosts(int& counter, stack<Position> stacks[4], Logger& log) {
	Position curGhostPos;
	int sample;

	switch (difficulty) {
	case Difficulty::BEST:
		sample = 5;
		break;
	case Difficulty::GOOD:
		sample = 10;
		break;
	}

	for (int i = 0; i < ghost.size(); i++) {
		if (difficulty != Difficulty::NOVICE) {
			if ((rand() % sample) == 0) {
				stacks[i] = ghost[i].findPath(pacman.getPosition(), map);
			}
			if (!stacks[i].empty()) {
				try {
					Direction dir = getDirectionFromStack(ghost[i].getPosition(), stacks[i].top());
					ghost[i].setDirection(dir);
					ghost[i].moveObject(map);
					log.logToStep("ghost " + to_string(i) + " moved " + dirToStr(dir));
					stacks[i].pop();
				}
				catch (exception) {
					stacks[i].empty();
					ghost[i].moveNovice(map, log, i);
				}
			}
			else
				ghost[i].moveNovice(map, log, i);
		}
		else
			ghost[i].moveNovice(map, log,  i);
	}
}

/*determines whether pacman stepped on a breadcrumb, if so
adds point to score and updates map at current pacman position to CORRIDOR char*/
void Game::updateBreadcrumbs() {
	Position pacmanPos = pacman.getPosition();

	if (map.getMapElement(pacmanPos) == BREADCRUMB) {      /*if stepped on breadcrumb*/
		map.setMapElement(pacmanPos, CORRIDOR);			/*update map*/
		addPointToScore();
		map.decreaseBreadcrumbCount();
	}
}

void Game::countdown() {
	printMessage("3");
	printMessage("2");
	printMessage("1");
	printMessage("Go!");
}


/*handles input from player, adjusts pacmans movement according to player input
or pauses the game if the key is ESC*/
void Game::handlePlayerInput(Logger& log) {
	char tempch;

	if (_kbhit()) {
		tempch = _getch();

		if (tempch == ESC)   /*if the key is ESC, pauses game*/
			pause();
		else
			pacman.adjustToInput(map, log, tempch);    /*a key was pressed, adjusts input based on key*/
	}
	else
		pacman.movePacman(map, log);     /*pacman continues natural movement if no key pressed*/

	pacman.useSecretTunnel(map);   /*if pacman arrives at tunnel, uses it*/
}


void Game::handleIsEaten(bool& game_over, Logger& log, int count) {
	if (isObjEatenByGhosts(pacman)) {
		decreaseLives();

		log.logToRes("--------------");
		log.logToRes(to_string(count));
		log.logToRes("pacman eaten");
		log.logToRes(to_string(lives) + " lives left");

		//for (int i = 0; i < ghost.size(); i++)
			//stacks[i] = {};

		if (lives == 0) {
			game_over = true;
		}
		else {
			pacmanEatenEvent();
		}
	}

	if (isObjEatenByGhosts(fruit)) {
		fruit.toggle(map, log);
		for (int i = 0; i < ghost.size(); i++)   
			ghost[i].teleportObject(ghost[i].getPosition(), map);
	}

	if (pacman.getPosition().isEqual(fruit.getPosition())) {
		fruit.toggle(map, log);
		score += (fruit.getchar() - '0');
		pacman.teleportObject(pacman.getPosition(), map); 
	}
}

bool Game::isObjEatenByGhosts(const Game_Object& obj) {
	Position objPos;
	Position tempGhostPos;

	objPos = obj.getPosition();

	for (int i = 0; i < ghost.size(); i++) { /*loops through all ghosts*/
		tempGhostPos = ghost[i].getPosition();

		if (objPos.isEqual(tempGhostPos))       /*compare position of current ghost and pacman*/
			return true;
	}
	return false;
}

Direction Game::getDirectionFromStack(const Position& ghost, const Position& stack) {
	int x = ghost.getX() - stack.getX();
	int y = ghost.getY() - stack.getY();

	if (x == 1 && y == 0)
		return Direction::LEFT;
	else if (x == -1 && y == 0)
		return Direction::RIGHT;
	else if (x == 0 && y == 1)
		return Direction::UP;
	else if (x == 0 && y == -1)
		return Direction::DOWN;
	else
		throw exception("invalid stack position");
}

