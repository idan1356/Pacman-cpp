#include "fruit.h"

char Fruit::getRandNum() const {
	char tempch;
	tempch = '5' + (rand() % 5);
	return tempch;
}

//toggles fruit between being active and being inactive
 void Fruit::toggle(Map& map, Logger& log) {
	 isActivated = !isActivated; 

	 if (isActivated == false) {
		 Position curPos = getPosition();
		 char mapElement = map.getMapElement(curPos);
		 curPos.draw(mapElement, DEFAULT_BREADCRUMB_COLOR);   //fruits disappear

		 setchar(getRandNum());     // sets fruit char to random num
		 curPos = map.getRandPositionOnMap();  

		 teleportObject(curPos, map, log);        //teleports fruit to a different location, remains hidden untill next toggle
		 mapElement = map.getMapElement(curPos);
		 curPos.draw(mapElement, DEFAULT_BREADCRUMB_COLOR);
		 setDirection(Direction::NONE);
	 }

	log.logToStep(logToggle());
 }

 //moves only when active
 void Fruit::moveNovice(Map& map, Logger& log, int i) {
	 if (isActivated)
		 Game_Object::moveNovice(map, log, -1);
 }


 string Fruit::logToggle() {
	 if (isActivated){
		 Position curPos = getPosition();
		 return "fruit appeared at " + to_string(curPos.getX()) + " " + to_string(curPos.getY());
	}
	 else
		 return "fruit disappeared";
 }
