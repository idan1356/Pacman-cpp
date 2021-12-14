#include "game_object.h"

/*constructor for game objects with all fields*/
Game_Object::Game_Object(char ch, Position pos, Direction dir, Color color, Position init_pos) :
	obj_char(ch), obj_pos(pos), obj_dir(dir), obj_color(color), obj_init_pos(init_pos){
	pos.draw(ch, obj_color);
}

Game_Object::Game_Object() : obj_char(' '), obj_pos(0,0), obj_dir(NONE), obj_color(WHITE), obj_init_pos(0, 0) {
}

/*given a game object, returns the next position its gonna be at,*/
/*according to its own direction (1 step ahead)*/
Position Game_Object::getNextPosition() {
	Position tempPos = obj_pos;
	tempPos.advance(obj_dir);
	return tempPos;
}

/*moves the object 1 step according to its direction*/
void Game_Object::moveObject(Map map) {
	char mapElement;

	mapElement = map.getMapElement(obj_pos);

	obj_pos.draw(mapElement, map.getBreadcrumbColor());
	obj_pos.advance(obj_dir);
	obj_pos.draw(obj_char, obj_color);
}

/*teleports object to a different location on map based on position given*/
void Game_Object::teleportObject(Position pos, Map map) {
	char mapElement;

	mapElement = map.getMapElement(obj_pos);
	obj_pos.draw(mapElement, map.getBreadcrumbColor());
	setPosition(pos);
	obj_pos.draw(obj_char, obj_color);
}


/*sets the game object's direction according to key*/
void Game_Object::setDirection(char key) {
	switch (key) {
	case 'W':
	case 'w':
		obj_dir = UP;
		break;
	case 'X':
	case 'x':
		obj_dir = DOWN;
		break;
	case 'A':
	case 'a':
		obj_dir = LEFT;
		break;
	case 'D':
	case 'd':
		obj_dir = RIGHT;
		break;
	case 'S':
	case 's':
		obj_dir = NONE;
	}
}

/*sets game object direction, given a direction*/
void Game_Object::setDirection( const Direction& direction) {
	obj_dir = direction;
}

void Game_Object::setPosition(const Position& position) {
	obj_pos = position;
}

/*moves object back to its initial position*/
void Game_Object::moveToInitPos(Map map) {
	Position objInitPosition;

	objInitPosition = getInitPosition();
	teleportObject(objInitPosition, map);
}

/*
  ghost movement function,
  when a ghost reaches an intersection, it decides randomally which direction to go
  based on available paths, but will not go backwards (in opposite direction)
  for game flow reasons
*/

void Game_Object::moveNovice(Map map) {
	Position tempPos;
	Direction tempDir, oppositeDir;

	oppositeDir = (Direction)((getDirection() + 2) % 4);
	tempPos = getNextPosition();

	do {
		tempDir = (Direction)(rand() % 4);   /*a random position is checked*/
		tempPos = getPosition();
		tempPos.advance(tempDir);

		if (map.isAtSecretTunnel(tempPos)) {
			tempDir = oppositeDir;
			break;
		}
	} while (!map.isPassable(tempPos) || tempDir == oppositeDir || map.isAtSecretTunnel(tempPos));

	setDirection(tempDir);
	moveObject(map);
}

