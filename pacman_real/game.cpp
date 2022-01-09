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
	countdown();

	while (gameOver == false) { 
		gotoxy(0, 0);
		cout << count << endl;

		log.newTurn(count);

		if(count == 0)
			fruit.toggle(map, log);

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
			moveGhosts(count, log);

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
void Game::pacmanEatenEvent(Logger& log) {
	printParameters();

	pacman.moveToInitPos(map, log);
	pacman.setDirection(Direction::NONE);

	for (int i = 0; i < ghost.size(); i++)
		ghost[i].moveToInitPos(map, log);

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
void Game::moveGhosts(int& counter, Logger& log) {
	for (int i = 0; i < ghost.size(); i++)
		if (difficulty == Difficulty::NOVICE)
			ghost[i].moveNovice(map, log, i);
		else
			ghost[i].move(map, i, difficulty, pacman.getPosition(), log);
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

	pacman.useSecretTunnel(map, log);   /*if pacman arrives at tunnel, uses it*/
}


void Game::handleIsEaten(bool& game_over, Logger& log, int count) {
	if (isObjEatenByGhosts(pacman)) {
		decreaseLives();

		log.logToRes("--------------");
		log.logToRes(to_string(count));
		log.logToRes("pacman eaten");
		log.logToRes(to_string(lives) + " lives left");

		if (lives == 0) {
			game_over = true;
		}
		else {
			pacmanEatenEvent(log);
			log.logToStep("teleport objs");
		}
	}

	if (isObjEatenByGhosts(fruit)) {
		fruit.toggle(map, log);
		for (int i = 0; i < ghost.size(); i++)   
			ghost[i].teleportObject(ghost[i].getPosition(), map, log);
	}

	if (pacman.getPosition().isEqual(fruit.getPosition())) {
		fruit.toggle(map, log);
		score += (fruit.getchar() - '0');
		pacman.teleportObject(pacman.getPosition(), map, log); 
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



