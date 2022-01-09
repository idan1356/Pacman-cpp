#include "game_replayer.h"

//reads game from files and checks for files validity
Game_State Game_Replayer::replay(bool silentFlag) {
	string buffer;
	Logger log;
	bool gameOver = false;
	int count = 0;

	hideCursor();
	getline(steps, buffer);
	getline(res, buffer);

	while (!steps.eof()) {
		gotoxy(0, 0);
		cout << count << endl;

		readStep(count);   

		if (!silentFlag)
			Sleep(5);

		pacman.moveObject(map); 
		pacman.useSecretTunnel(map, log);
		updateBreadcrumbs();

		if (map.getBreadcrumbCount() == 0 && isClearedLogged(count)) {
			break;
		}
		else if (map.getBreadcrumbCount() == 0 && !isClearedLogged(count))
			throw runtime_error("invalid log in res file");

		for (auto& cur : ghost) { 
			if (count % 2 == 0)
			cur.moveObject(map);
		}

		if (fruit.getIsActivated() && (count % 3) == 0)
			fruit.moveObject(map);
			
		printParameters();
		count++;
	}

	Game_State state = { lives, score };
	return  state;
}

// read one game loop iteration and sets game objects direction accordingly
void Game_Replayer::readStep(int count) {
	string buffer; Logger log;
	getline(steps, buffer);

	if (count != stoi(buffer))
		throw runtime_error("invalid count of steps file");

	while (!steps.eof() && buffer.at(0) != '-') {
		getline(steps, buffer);

		if (buffer == "teleport objs" && isEatenLogged(count)) {
			pacmanEatenEvent(log);
			decreaseLives();
		}
		parseLine(buffer);  
	}
}

//parses string in result file to command to specific game object
void Game_Replayer::parseLine(const string& line) {
	std::stringstream iss(line);
	string buffer; bool temp;
	Direction dir;
	Game_Object* obj = nullptr;
	Logger log;
	int x, y;

	iss >> buffer;    //converts line into stream and reads word by word

	if (buffer == "pacman")
		obj = &pacman;
	else if (buffer == "fruit")
		obj = &fruit;
	else if (buffer == "ghost") {
		iss >> buffer;
		int ind = stoi(buffer);
		obj = &ghost[ind];
	}

	iss >> buffer;
	if (buffer == "moved") {
		iss >> buffer;
		Direction dir = strToDir(buffer);
		obj->setDirection(dir);

		if (!map.isPassable(obj->getNextPosition()))
			throw invalid_argument("invalid step for one of the objects");
	}

	else if (buffer == "disappeared"){
		fruit.toggle(map, log);
	}
	else if (buffer == "appeared") {
		fruit.toggle(map, log);
		iss >> buffer;
		iss >> buffer;
		x = stoi(buffer);
		iss >> buffer;
		y = stoi(buffer);

		Position pos = { x, y };
		fruit.teleportObject(pos, map, log);
	}
}

//converts string into direction
Direction Game_Replayer::strToDir(string str) {
	if (str == "up")
		return Direction::UP;
	else if (str == "down")
		return Direction::DOWN;
	else if (str == "left")
		return Direction::LEFT;
	else if (str == "right")
		return Direction::RIGHT;
	else if (str == "inplace")
		return Direction::NONE;
	else
		throw invalid_argument("invalid direction given at result file");
}

//checks if pacman eaten logged in result file in current iteration of the replayer, given corrent count
bool Game_Replayer::isEatenLogged(int count) {
	string buffer;
	vector<string> vec;
	getline(res, buffer);

	while (buffer[0] != '-' && !res.eof()) {
		vec.push_back(buffer);
		getline(res, buffer);
	} 

	int vecSize = vec.size();

	if(vecSize >= 3)
		vec[2] = vec[2].substr(0, vec[2].find(' '));

	if (stoi(vec[0]) == count && vec[1] == "pacman eaten" &&
		stoi(vec[2]) == lives - 1 && vecSize == 3 || vecSize == 4) {

		if (lives - 1 == 0 && vec.size() == 4 && vec[3] == "level lost") {
			clear_screen();
			cout << "test passed";
			return false;
		}

		else
			return true;

	}
	else
		throw invalid_argument("invalid log in result file");
}


void Game_Replayer::handleIsEatenRec(int& count,Logger& log,bool& gameOver) {
	string buffer;

	if ((isObjEatenByGhosts(pacman) && isEatenLogged(count)) || isObjEatenByGhosts(fruit)) {
		handleIsEaten(gameOver, log, count);
	}

}

// checks if level cleared event is logged in result file and synced with the current count
bool Game_Replayer::isClearedLogged(int& count) {
	string buffer;
	getline(res, buffer);

	return (buffer == "level cleared");
}

