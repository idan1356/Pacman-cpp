#include "game_initializer.h"

/*iterates through all cells and innitiates each one*/
void Game_Initializer::initMap() {
	Position tempPos;
	int mapLength, mapWidth;

	mapLength = map.getLength();
	mapWidth = map.getWidth();

	for (int i = 0; i < mapLength; i++)
		for (int j = 0; j < mapWidth - 1; j++) {
			tempPos = Position(j, i);
			initCell(tempPos);
		}
}

/*innitiates current cell based on what type of char it contains*/
void Game_Initializer::initCell(Position pos) {
	char mapElement;

	mapElement = map.getMapElement(pos);

	switch (mapElement) {
	case CORRIDOR:    /*if current cell has ' ' char, adds a breadcrumb to it and increases breadcrumb count*/
		map.setMapElement(pos, BREADCRUMB);
		pos.draw(BREADCRUMB, map.getBreadcrumbColor());
		map.increaseBreadcrumbCount();
		break;
	case NO_BREADCRUMB_CORRIDOR:       
		map.setMapElement(pos, CORRIDOR);
		pos.draw(CORRIDOR, WHITE);
		break;
	case GHOST_CHAR:
		map.setMapElement(pos, CORRIDOR);
		ghost.push_back(Ghost(pos, colorOrder[ghost.size()]));
		break;
	case PACMAN_CHAR:
		pacman.push_back(Pacman(pos, YELLOW));
		map.setMapElement(pos, BREADCRUMB);
		map.increaseBreadcrumbCount();
		break;
	default:
		pos.draw(WALL, map.getMapColor());
		break;
	}
}