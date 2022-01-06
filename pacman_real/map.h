#ifndef _MAP_H_
#define _MAP_H_

#include "position.h"

class Map {
private:
	string	map_name;
	Color	map_color = DEFAULT_MAP_COLOR;
	Color	breadcrumb_color = DEFAULT_BREADCRUMB_COLOR;
	int		breadcrumbCount = 0;
	int		map_length;
	int		map_width;
	char	map[DEFAULT_MAP_WIDTH][DEFAULT_MAP_LENGTH];
	bool	isValid = true;
public:
	Map(string file_name, bool colorMode);

	Color getBreadcrumbColor() const {return breadcrumb_color;};
	Color getMapColor() const { return map_color; };
	Position getRandPositionOnMap() const;
	void getDimensions();
	const string& getMapName() const { return map_name; };
	void setMapElement(const Position& pos, char ch);
	void increaseBreadcrumbCount() { breadcrumbCount++; };
	void decreaseBreadcrumbCount() { breadcrumbCount--; };

	void printMap() const;
	void fixMap();
	void addLegend(const Position& pos, bool colorMode);

	int getLength() const { return map_length; };
	int getWidth() const { return map_width; };
	int getBreadcrumbCount() const { return breadcrumbCount; };
	bool getIsValidMap() const { return isValid; };
	char getMapElement(const Position& pos) const;

	bool isAtSecretTunnel(const Position& pos) const;
	bool isPassable(const Position& pos) const;
	bool isInBounds(const Position& pos) const;
};

#endif
