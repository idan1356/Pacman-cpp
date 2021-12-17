#include "pacman.h"


/*this function is called after a key is pressed.adjusts pacmans movement
according to key pressed*/
void Pacman::adjustToInput(Map map, char ch) {
	Position tempPos;
	Direction tempDir;

	tempDir = keyToDirection(ch);

	if (tempDir != INVALID_KEY) {
		tempPos = getPosition();
		tempPos.advance(tempDir);

		if (map.isPassable(tempPos)) {
			setDirection(ch); /*movement change will only occur if the next step is a passable corridor*/
		}	
		movePacman(map);

	}
}

/*moves pacman if no key was pressed. */
void Pacman::movePacman(Map map) {
	Position tempPos;

	tempPos = getNextPosition();

	if (map.isPassable(tempPos))      /*movement will only occur if the next step is a passable corridor*/
		moveObject(map);
}

/*teleports pacman to the other side of the tunnel if at tunnel enterance*/
void Pacman::useSecretTunnel(Map map) {
	Position curPos, newPos;
	int mapWidth, mapLength;
	int x, y;

	curPos = getPosition();
	x = curPos.getX();
	y = curPos.getY();

	mapWidth = map.getWidth();
	mapLength = map.getLength();

	if (x == 0) 
		x = mapWidth - 2;
	else if (x == mapWidth - 2)
		x = 0;
	else if (y == 0)
		y = mapLength - 1;
	else if (y == mapLength - 1)
		y = 0;

	newPos = Position(x, y);
	if(map.getMapElement(Position(x, y)) == CORRIDOR)
		teleportObject(newPos, map);
}

