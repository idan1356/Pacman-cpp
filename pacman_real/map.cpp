#include "map.h"

/*initiates map to default map*/
Map::Map(string file_name) {
	int i = 1;
	fstream file;
	string buffer;

	file.open(file_name);
	if (!file) {
		isValid = false;
		return;
	}

	getline(file, buffer);
	strcpy(map[0], buffer.data());
	if (buffer.size() > DEFAULT_MAP_LENGTH) {
		isValid = false;
		return;
	}
	else {

		while (!file.eof()) {
			getline(file, buffer);
			strcpy(map[i], buffer.data());
			i++;

			if (i > DEFAULT_MAP_WIDTH) {
				isValid = false;
				return;
			}
		}

		map_width = strlen(map[0]) + 1;
		map_length = i;
	}
}


/* the map element at a certain position*/
char Map::getMapElement(Position pos) {
	int curX = pos.getX();
	int curY = pos.getY();

	return map[curY][curX];
}

/*prints map on console*/
void Map::printMap() {
	setTextColor(BLUE);
	for (int i = 0; i < map_length; i++) 
		cout << map[i] << endl;
	
	setTextColor(WHITE);
}

/*checks if a given position on map is passable for game objects*/
bool Map::isPassable(Position pos) {
	char ch = getMapElement(pos);
	return ch == CORRIDOR || ch == BREADCRUMB || ch == NO_BREADCRUMB_CORRIDOR;
}

/*checks if a given position is located at any of the tunnel enterances*/
bool Map::isAtSecretTunnel(Position pos) {
	if (pos.getX() == 0 || pos.getX() == map_width - 1 || pos.getY() == 0 || pos.getY() == map_length - 1) {
		return true;
	}
	else
		return false;
}

/*writes char to map*/
void Map::setMapElement(Position pos, char ch) {
	int posX, posY;

	posX = pos.getX();
	posY = pos.getY();

	map[posY][posX] = ch;
}


Position Map::getRandPositionOnMap() {
	Position pos;
	do {
		pos = { (rand() % getWidth()), rand() % getLength() };

	} while (!isPassable(pos));

	return pos;
}


