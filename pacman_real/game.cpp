#include "game.h"
#include "stack"
//game loop
Game_State Game::start() {
	int count;
	bool gameOver;
	stack<Position> stacks[4];
	count = 0;
	gameOver = false;
	hideCursor();
	countdown();

	while (gameOver == false) {      
		handleIsEaten(gameOver, stacks);
		Sleep(GAME_SPEED);
		handlePlayerInput();     /*handles pacman movementand pause status according to player input*/
		updateBreadcrumbs();     /*updates breadcrumb based on pacmans location*/
		handleIsEaten(gameOver, stacks);

		if (map.getBreadcrumbCount() == 0)  
			gameOver = true;
		if (count % 2 == 0) 
			moveGhosts(count, stacks);
		if (count % 3 == 1)
			fruit.moveNovice(map);

		printParameters();
		count++;

		if ((rand() % 55) == 1)
			fruit.toggle(map);
	}

	clear_screen();
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
void Game::printParameters() {
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
	pacman.setDirection(NONE);

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

	setTextColor(WHITE);
}

/*iterates through the array of ghosts and moves them 1 step*/
void Game::moveGhosts(int counter, stack<Position> stacks[4]) {
	//stack<Position> stacks[4]; 
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
				ghost[i].teleportObject(stacks[i].top(), map);
				stacks[i].pop();
			}
			else
				ghost[i].moveNovice(map);
		}
		else
			ghost[i].moveNovice(map);
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
void Game::handlePlayerInput() {
	char tempch;

	if (_kbhit()) {
		tempch = _getch();

		if (tempch == ESC)   /*if the key is ESC, pauses game*/
			pause();
		else
			pacman.adjustToInput(map, tempch);    /*a key was pressed, adjusts input based on key*/
	}
	else
		pacman.movePacman(map);     /*pacman continues natural movement if no key pressed*/

	pacman.useSecretTunnel(map);   /*if pacman arrives at tunnel, uses it*/
}


void Game::handleIsEaten(bool& game_over, stack<Position> stacks[4]) {
	if (isObjEatenByGhosts(pacman)) {
		decreaseLives();

		for (int i = 0; i < ghost.size(); i++)
			stacks[i] = {};

		if (lives == 0)
			game_over = true;
		else
			pacmanEatenEvent();
	}

	if (isObjEatenByGhosts(fruit)) {
		fruit.toggle(map);
		for (int i = 0; i < ghost.size(); i++)   
			ghost[i].teleportObject(ghost[i].getPosition(), map);
	}

	if (pacman.getPosition().isEqual(fruit.getPosition())) {
		fruit.toggle(map);
		score += (fruit.getchar() - '0');
		pacman.teleportObject(pacman.getPosition(), map); 
	}
}

bool Game::isObjEatenByGhosts(const Game_Object& obj) const {
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


