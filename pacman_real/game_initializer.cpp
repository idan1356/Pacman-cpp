#include "game_initializer.h"

/*iterates through all cells and innitiates each one*/
void Game_Initializer::initMap() {
	Position tempPos;
	int mapLength, mapWidth;
	map.getDimensions();

	mapLength = map.getLength();
	mapWidth = map.getWidth();
	
	for (int i = 0; i < DEFAULT_MAP_WIDTH - 1; i++)
		for (int j = 0; j < DEFAULT_MAP_LENGTH - 2; j++) {
			tempPos = Position(j, i);
			initCell(tempPos);
		}

	map.addLegend(legend, colorMode);
}

/*innitiates current cell based on what type of char it contains*/
void Game_Initializer::initCell(Position pos) {
	char mapElement;

	mapElement = map.getMapElement(pos);

	switch (mapElement) {
	case CORRIDOR:    /*if current cell has ' ' char, adds a breadcrumb to it and increases breadcrumb count*/
		if (map.isInBounds(pos)) {
			map.setMapElement(pos, BREADCRUMB);

			if(colorMode)
				pos.draw(BREADCRUMB, map.getBreadcrumbColor());
			else
				pos.draw(BREADCRUMB, WHITE);

			map.increaseBreadcrumbCount();
		}

		break;
	case NO_BREADCRUMB_CORRIDOR: 
		if (map.isInBounds(pos)) {
			map.setMapElement(pos, CORRIDOR);
			pos.draw(CORRIDOR, WHITE);
		}
		break;
	case GHOST_CHAR:
		if (map.isInBounds(pos)) {
			map.setMapElement(pos, CORRIDOR);
			if(colorMode)
				ghost.push_back(Ghost(pos, colorOrder[ghost.size()]));
			else
				ghost.push_back(Ghost(pos, WHITE));
		}
		break;
	case PACMAN_CHAR:
		if (map.isInBounds(pos)) {
			if(colorMode)
				pacman.push_back(Pacman(pos, YELLOW));
			else
				pacman.push_back(Pacman(pos, WHITE));

			map.setMapElement(pos, BREADCRUMB);
			map.increaseBreadcrumbCount();
		}
		break;
	case '&':
		legend = pos;
	default:
		if (map.isInBounds(pos)) {
			if(colorMode)
				pos.draw(WALL, map.getMapColor());
			else
				pos.draw(WALL, WHITE);
		}
		break;
	}
}









