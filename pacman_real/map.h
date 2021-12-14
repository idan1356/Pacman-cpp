#ifndef _MAP_H_
#define _MAP_H_

#include "position.h"

class Map {
private:
	Color map_color = DEFAULT_MAP_COLOR;
	Color breadcrumb_color = DEFAULT_BREADCRUMB_COLOR;
	int	 breadcrumbCount = 0;
	int  map_length;
	int  map_width;
	char map[DEFAULT_MAP_WIDTH][DEFAULT_MAP_LENGTH];
	bool isValid = true;
public:
	Map(string file_name);
	
	Color getBreadcrumbColor() {return breadcrumb_color;};
	Color getMapColor() { return map_color; };

	Position getRandPositionOnMap();
 
	void setMapElement(Position pos, char ch);
	void increaseBreadcrumbCount() { breadcrumbCount++; };
	void decreaseBreadcrumbCount() { breadcrumbCount--; };

	void printMap();

	int getLength() const { return map_length; };
	int getWidth() const { return map_width; };
	int getBreadcrumbCount() const { return breadcrumbCount; };
	bool getIsValidMap() const { return isValid; };
	char getMapElement(Position pos);

	bool isAtSecretTunnel(Position pos);
	bool isPassable(Position pos);
};

#endif
