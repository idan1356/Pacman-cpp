#include "map.h"

/*initiates map to default map*/
Map::Map(string file_name, bool colorMode) {
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

	if (colorMode) {
		map_color = DEFAULT_MAP_COLOR;
		breadcrumb_color = DEFAULT_BREADCRUMB_COLOR;
	}
	else {
		map_color = Color::WHITE;
		breadcrumb_color = Color::WHITE;
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
	setTextColor(Color::BLUE);
	for (int i = 0; i < map_length; i++) 
		cout << map[i] << endl;
	
	setTextColor(Color::WHITE);
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


bool Map::isInBounds(Position pos) {
	return ((pos.getX() <= getWidth() - 1) && (pos.getY() <= getLength() - 1));
}
void Map::addLegend(Position pos, bool colorMode) {
	char legend[3][20] = { "###################",
					   "#                 #",
					   "###################"
	};

	int posX = pos.getX();
	int posY = pos.getY();

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 20; i++) {
			map[posY + j][posX + i] = legend[j][i];
			Position pos = Position(posX + i, posY + j);
			if(colorMode)
				pos.draw(legend[j][i], Color::BLUE);
			else
				pos.draw(legend[j][i], Color::WHITE);
		}
}

void Map::getDimensions() {
	int length = getLength();
	int cur = 0;
	bool foundEnd = false;
	for (int i = 0; i < length; i++) {
		if (map[i][0] == CORRIDOR && foundEnd == false) {
			cur = i - 1;
			foundEnd = true;
		}

		if (map[i][0] == WALL) {
			cur = i;
			foundEnd = false;
		}
	}

	map_length = cur + 1;
}

void Map::fixMap() {
	Position pos;

	for (int i = 0; i < 20; i++) {
		pos = Position(40 + i, 19);
		pos.draw(map[19][40 + i], map_color);
	}

}