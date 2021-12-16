#include "ghost.h"


void Ghost::findPath(Position pacman, Map& map) {
	A_Node* arr[DEFAULT_MAP_LENGTH][DEFAULT_MAP_WIDTH]{};
	priority_queue<A_Node*, vector<A_Node*>, CustomCompare> open; //////fix operator!!!!!!

	A_Node* curNode = nullptr;
	Position curPos = getPosition();
	A_Node* curNeighbor = nullptr;

	arr[curPos.getY()][curPos.getX()] = new A_Node(curPos);
	curNode = arr[curPos.getY()][curPos.getX()];
	open.push(curNode);

	while (!open.empty()) {
		curNode = open.top();
		open.pop();
		curNode->setClose();
		if (curNode->getPosition().isEqual(pacman))
			break;

		for (int i = 0; i < 4; i++) {
			curPos = curNode->getPosition();
			curPos.advance(Direction(i));
			curNeighbor = arr[curPos.getY()][curPos.getX()];
			if (map.isPassable(curPos) && map.isInBounds(curPos)) {
				if (curNeighbor == nullptr)
					curNeighbor = new A_Node(*curNode, curPos, pacman);
				else if (curNeighbor->getIsOpen())
					curNeighbor->update_Node(*curNode, pacman);
				else
					continue;

				if (!curNeighbor->getIsOpen()) {
					open.push(curNeighbor);
					curNeighbor->setOpen();
				}
			}
		}
	}

	while (curNode != nullptr) {
		curNode->getPosition().draw('*', WHITE);
		curNode = curNode->getParent();
	}

}

