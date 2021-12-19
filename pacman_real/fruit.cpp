#include "fruit.h"

char Fruit::getRandNum() const {
	char tempch;
	tempch = '5' + (rand() % 5);
	return tempch;
}

//toggles fruit between being active and being inactive
 void Fruit::toggle(Map& map) {
	 isActivated = (isActivated + 1) % 2; 

	 if (isActivated == false) {
		 Position curPos = getPosition();
		 char mapElement = map.getMapElement(curPos);
		 curPos.draw(mapElement, DEFAULT_BREADCRUMB_COLOR);   //fruits disappear

		 setchar(getRandNum());     // sets fruit char to random num

		 curPos = map.getRandPositionOnMap();  
		 teleportObject(curPos, map);        //teleports fruit to a different location, remains hidden untill next toggle
		 mapElement = map.getMapElement(curPos);
		 curPos.draw(mapElement, DEFAULT_BREADCRUMB_COLOR);
	 }

 }

 //moves only when active
 void Fruit::moveNovice(Map& map) {
	 if (isActivated)
		 Game_Object::moveNovice(map);
 }
